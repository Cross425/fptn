include $(TOPDIR)/rules.mk

PKG_NAME:=fptn-client-cli
PKG_VERSION:=0.3.34
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/batchar2/fptn.git
PKG_SOURCE_VERSION:=master

PKG_MAINTAINER:=you
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn-client-cli
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client CLI
  DEPENDS:=+libc +libstdcpp +ip-full +iptables
endef

define Package/fptn-client-cli/description
FPTN client CLI for OpenWrt (filogic / AX3000T).
endef

CMAKE_OPTIONS += \
  -DFPTN_BUILD_GUI_CLIENT=OFF \
  -DFPTN_BUILD_ONLY_FPTN_LIB=OFF \
  -DBUILD_TESTING=OFF \
  -DFPTN_ENABLE_TUNTAP=OFF \
  -DENABLE_TUNTAP=OFF

define Build/Prepare
	$(call Build/Prepare/Default)
endef

define Build/Configure
	$(call Build/Configure/Default)
endef

define Package/fptn-client-cli/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/fptn-client-cli $(1)/usr/bin/
endef

$(eval $(call BuildPackage,fptn-client-cli))
