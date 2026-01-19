include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=0.3.35
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/batchar2/fptn.git
PKG_SOURCE_VERSION:=v$(PKG_VERSION)

PKG_LICENSE:=MIT

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN (experimental) for OpenWrt
  DEPENDS:=+libstdcpp +kmod-tun +ca-bundle
endef

define Package/fptn/description
  FPTN VPN client (experimental OpenWrt build).
endef

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/fptn $(1)/usr/sbin/fptn

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/fptn.init $(1)/etc/init.d/fptn
endef

$(eval $(call BuildPackage,fptn))
