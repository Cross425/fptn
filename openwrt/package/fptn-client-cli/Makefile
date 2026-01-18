include $(TOPDIR)/rules.mk

PKG_NAME:=fptn-client-cli
PKG_VERSION:=0.3.34
PKG_RELEASE:=1

# No sources built in OpenWrt SDK (we package a prebuilt binary from files/)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/fptn-client-cli
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client CLI (prebuilt)
  DEPENDS:=+libstdcpp +libpthread
endef

define Package/fptn-client-cli/description
  Prebuilt fptn-client-cli binary cross-built in CI and packaged with OpenWrt SDK
  to produce a correct .apk for OpenWrt 25.12.
endef

define Build/Configure
	# nothing
endef

define Build/Compile
	# nothing
endef

define Package/fptn-client-cli/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/usr/bin/fptn-client-cli $(1)/usr/bin/fptn-client-cli
endef

$(eval $(call BuildPackage,fptn-client-cli))
