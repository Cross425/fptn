include $(TOPDIR)/rules.mk
PKG_NAME:=fptn-client-cli
PKG_VERSION:=0.3.34
PKG_RELEASE:=3
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/batchar2/fptn.git
PKG_SOURCE_VERSION:=master
PKG_MIRROR_HASH:=skip
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk
CMAKE_OPTIONS+= -DFETCHCONTENT_FULLY_DISCONNECTED=ON -DBUILD_TESTING=OFF
define Package/fptn-client-cli
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client CLI
endef
define Build/Compile
	cd $(PKG_BUILD_DIR) && conan install . -pr:h=openwrt-a53 -pr:b=default --build=missing
	$(call Build/Compile/Default)
endef
define Package/fptn-client-cli/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/fptn-client-cli $(1)/usr/bin/fptn-client-cli
endef
$(eval $(call BuildPackage,fptn-client-cli))
