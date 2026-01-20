include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=git
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/batchar2/fptn.git
PKG_SOURCE_VERSION:=HEAD
PKG_MIRROR_HASH:=skip

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=fptn client
  DEPENDS:=+libstdcpp +libpthread +librt
endef

define Package/fptn/description
fptn client (built from upstream git).
endef

CMAKE_OPTIONS += \
  -DCMAKE_BUILD_TYPE=Release

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/fptn $(1)/usr/bin/fptn || true

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/fptn.init $(1)/etc/init.d/fptn
endef

$(eval $(call BuildPackage,fptn))
