include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=2026-01-26
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Cross425/fptn.git
PKG_SOURCE_VERSION:=master

PKG_BUILD_DEPENDS:=protobuf/host

PKG_MAINTAINER:=Cross425
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS += \
	-DFPTN_NO_FETCHCONTENT=ON \
	-DFPTN_DISABLE_WERROR=ON

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=VPN
  TITLE:=FPTN VPN (client CLI)
  URL:=https://github.com/batchar2/fptn
  DEPENDS:=+libstdcpp +libopenssl +zlib +kmod-tun +ip-full +ca-bundle +protobuf +libprotobuf +libidn2 +re2
endef

define Package/fptn/description
FPTN client CLI packaged for OpenWrt.
Includes procd service and a simple "route all traffic via tun0" policy routing script.
endef

define Package/fptn/conffiles
/etc/config/fptn
/etc/fptn/client.conf
endef

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/bin
	# upstream installs into DESTINATION bin -> staged as /bin/fptn-client-cli
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/fptn-client-cli $(1)/usr/bin/fptn

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/fptn.init $(1)/etc/init.d/fptn

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/fptn.config $(1)/etc/config/fptn

	$(INSTALL_DIR) $(1)/usr/lib/fptn
	$(INSTALL_BIN) ./files/fptn-route.sh $(1)/usr/lib/fptn/route.sh

	$(INSTALL_DIR) $(1)/etc/fptn
	# user should replace this with a real config from their server
	$(INSTALL_CONF) ./files/client.conf.example $(1)/etc/fptn/client.conf
endef

$(eval $(call BuildPackage,fptn))
