include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=0.3.35
PKG_RELEASE:=1

# Upstream tag is "0.3.35" (without fptn- prefix)
PKG_SOURCE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/batchar2/fptn/archive/refs/tags
PKG_HASH:=a27989a759cee751686a9ec95eb37dfcb42d4d2c46b125b2c975e991fab20660

# GitHub archive extracts to: fptn-<version>
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_SOURCE_SUBDIR)

PKG_MAINTAINER:=
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/fptn-client-cli
  SECTION:=net
  CATEGORY:=Network
  TITLE:=fptn client CLI
  URL:=https://github.com/batchar2/fptn
  DEPENDS:=+libstdcpp +libcurl +libopenssl +zlib
endef

define Package/fptn-client-cli/description
  fptn client CLI.
endef

CMAKE_OPTIONS += \
	-DCMAKE_BUILD_TYPE=Release

# If upstream adds a proper install() target later:
#   CMAKE_INSTALL:=1
#   then copy from $(PKG_INSTALL_DIR)

define Package/fptn-client-cli/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/src/fptn-client/fptn-client-cli $(1)/usr/bin/
endef

$(eval $(call BuildPackage,fptn-client-cli))
