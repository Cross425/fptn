include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=0.3.35
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Cross425/fptn.git
PKG_SOURCE_VERSION:=0.3.35
PKG_MIRROR_HASH:=skip

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client
  DEPENDS:=+libstdcpp
endef

define Package/fptn/description
  FPTN client package for OpenWrt
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fptn-client $(1)/usr/bin/fptn
endef

$(eval $(call BuildPackage,fptn))
