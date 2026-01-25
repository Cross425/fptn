#!/bin/sh
# route.sh: simple policy routing for "all traffic via tun0"
# Usage:
#   /usr/lib/fptn/route.sh <VPN_SERVER_IP>
#   /usr/lib/fptn/route.sh --down

set -eu

TUN_IF="tun0"
TABLE_ID="100"
TABLE_NAME="fptn"
RULE_ALL_PREF="10000"
RULE_VPNSERVER_PREF="1000"
RULE_LAN_PREF="900"

ensure_tables() {
	[ -f /etc/iproute2/rt_tables ] || return 0
	grep -qE "^[[:space:]]*${TABLE_ID}[[:space:]]+${TABLE_NAME}\$" /etc/iproute2/rt_tables 2>/dev/null && return 0
	echo "${TABLE_ID} ${TABLE_NAME}" >> /etc/iproute2/rt_tables
}

wait_tun() {
	for i in $(seq 1 30); do
		ip link show "$TUN_IF" >/dev/null 2>&1 && return 0
		sleep 1
	done
	return 1
}

down() {
	# Remove rules/routes (best effort)
	ip rule del pref "$RULE_ALL_PREF" 2>/dev/null || true
	ip rule del pref "$RULE_VPNSERVER_PREF" 2>/dev/null || true
	ip rule del pref "$RULE_LAN_PREF" 2>/dev/null || true
	ip route flush table "$TABLE_NAME" 2>/dev/null || true
	ip route flush table "$TABLE_ID" 2>/dev/null || true
}

if [ "${1:-}" = "--down" ]; then
	down
	exit 0
fi

VPN_SERVER_IP="${1:-}"
if [ -z "$VPN_SERVER_IP" ]; then
	echo "Usage: $0 <VPN_SERVER_IP> | --down" >&2
	exit 2
fi

ensure_tables

# wait for tun0
wait_tun || {
	echo "tun interface ${TUN_IF} not found" >&2
	exit 1
}

# Default route via tun0 in table fptn
ip route replace default dev "$TUN_IF" table "$TABLE_NAME" 2>/dev/null || ip route replace default dev "$TUN_IF" table "$TABLE_ID"

# Rule: all traffic -> table fptn
ip rule add pref "$RULE_ALL_PREF" lookup "$TABLE_NAME" 2>/dev/null || true
ip rule add pref "$RULE_ALL_PREF" lookup "$TABLE_ID" 2>/dev/null || true

# Exception: traffic to VPN server must use main (WAN), otherwise routing loop
ip rule add pref "$RULE_VPNSERVER_PREF" to "$VPN_SERVER_IP"/32 lookup main 2>/dev/null || true

# Optional: keep private LAN ranges on main to preserve access to router/LAN
keep_lan="$(uci -q get fptn.main.keep_lan || echo 1)"
if [ "$keep_lan" = "1" ]; then
	ip rule add pref "$RULE_LAN_PREF" to 192.168.0.0/16 lookup main 2>/dev/null || true
	ip rule add pref "$RULE_LAN_PREF" to 10.0.0.0/8 lookup main 2>/dev/null || true
	ip rule add pref "$RULE_LAN_PREF" to 172.16.0.0/12 lookup main 2>/dev/null || true
fi

exit 0
