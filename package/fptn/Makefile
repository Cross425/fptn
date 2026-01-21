include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=git
PKG_RELEASE:=3

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/Cross425/fptn.git
PKG_SOURCE_VERSION:=a4634d4
PKG_MIRROR_HASH:=skip

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=fptn client (OpenWrt)
  DEPENDS:=+libstdcpp +libpthread +librt
endef

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release -DFPTN_NO_FETCHCONTENT=ON -DFPTN_DISABLE_OPENSSL_KEYLOG=ON

define Build/Prepare
	$(call Build/Prepare/Default)
	cp -r ./vendor $(PKG_BUILD_DIR)/
endef

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/fptn $(1)/usr/bin/fptn || true
endef

$(eval $(call BuildPackage,fptn))
