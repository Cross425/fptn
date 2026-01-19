include $(TOPDIR)/rules.mk

PKG_NAME:=fptn
PKG_VERSION:=0.3.35
PKG_RELEASE:=1

# GitHub tag is "0.3.35" (without fptn- prefix)
PKG_SOURCE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/batchar2/fptn/archive/refs/tags
PKG_HASH:=a27989a759cee751686a9ec95eb37dfcb42d4d2c46b125b2c975e991fab20660

PKG_MAINTAINER:=
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/fptn
  SECTION:=net
  CATEGORY:=Network
  TITLE:=fptn
  URL:=https://github.com/batchar2/fptn
endef

define Package/fptn/description
  fptn client CLI.
endef

# NOTE: Keep your existing Build/Compile and Package/install sections below,
# or replace this whole file with your current Makefile and ONLY update the
# PKG_SOURCE / PKG_SOURCE_URL / PKG_HASH lines above.

$(eval $(call BuildPackage,fptn))
