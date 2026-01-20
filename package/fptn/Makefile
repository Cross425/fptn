include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=0.3.35
PKG_RELEASE:=25

# GitHub tag is "0.3.35"
PKG_SOURCE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/batchar2/fptn/archive/refs/tags
PKG_HASH:=a27989a759cee751686a9ec95eb37dfcb42d4d2c46b125b2c975e991fab20660
PKG_SOURCE_SUBDIR:=fptn-$(PKG_VERSION)

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FPTN client CLI
  DEPENDS:=\
    +libstdcpp \
    +libpthread \
    +zlib \
    +libatomic \
    +kmod-tun \
    +ca-bundle
endef

define Package/fptn/description
  FPTN client CLI for OpenWrt (builds fptn-client-cli).
endef

# Upstream requires FPTN_VERSION
CMAKE_OPTIONS += \
  -DFPTN_VERSION=$(PKG_VERSION) \
  -DFPTN_BUILD_WITH_GUI_CLIENT=OFF \
  -DFPTN_BUILD_ONLY_FPTN_LIB=OFF \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_FLAGS="-Wno-error"

define Package/fptn/install
	$(INSTALL_DIR) $(1)/usr/bin
	# Upstream installs targets to "bin" (see install(TARGETS ... DESTINATION bin))
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/fptn-client-cli $(1)/usr/bin/fptn-client-cli
endef

$(eval $(call BuildPackage,fptn))
