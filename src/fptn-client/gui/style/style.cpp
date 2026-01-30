/*=============================================================================
Copyright (c) 2024-2025 Stas Skokov

Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/

#include "gui/style/style.h"

namespace fptn::gui {
QString macStyleSheet = R"(
QMenu {
    background-color: #333;
    color: #fff;
    border: 1px solid #555;
}
QMenu::item {
    background-color: #333;
    color: #fff;
    padding: 5px 5px;
}
QMenu::item:selected {
    background-color: #555;
    color: #fff;
}
QMenu::icon {
    margin-right: 10px;
}
QAction {
    color: #fff;
}
QWidgetAction {
    padding: 5px;
}
)";

QString ubuntuStyleSheet = R"(
QMenu {
    background-color: #ffffff;
    color: #333333;
    border: 1px solid #d0d0d0;
    border-radius: 8px;
    padding: 0;
}
QMenu::item {
    background-color: #ffffff;
    color: #333333;
    padding: 8px 12px;
    border-radius: 4px;
}
QMenu::item:selected {
    background-color: #e0e0e0;
    color: #333333;
}
QMenu::icon {
    margin-right: 8px;
}
QAction {
    color: #333333;
}
QWidgetAction {
    padding: 8px 12px;
}
QWidget {
    font-family: 'Ubuntu', 'Segoe UI', Tahoma, Verdana, Arial, sans-serif;
    font-size: 11pt;
    color: #333333;
    background-color: #f0f0f0;
}
QPushButton {
    background-color: #ffffff;
    color: #333333;
    border: 1px solid #d0d0d0;
    border-radius: 4px;
    padding: 6px 12px;
}
QPushButton:hover {
    background-color: #e0e0e0;
}
QPushButton:pressed {
    background-color: #d0d0d0;
}
QLineEdit, QTextEdit {
    background-color: #ffffff;
    color: #333333;
    border: 1px solid #d0d0d0;
    border-radius: 4px;
    padding: 4px 8px;
}
QCheckBox, QRadioButton {
    color: #333333;
}
QSlider::groove:horizontal {
    border: 1px solid #d0d0d0;
    height: 8px;
    background: #ffffff;
    border-radius: 4px;
}
QSlider::handle:horizontal {
    background: #333333;
    border: 1px solid #d0d0d0;
    width: 16px;
    border-radius: 4px;
}
QScrollBar:vertical {
    border: 1px solid #d0d0d0;
    background: #ffffff;
    width: 16px;
}
QScrollBar::handle:vertical {
    background: #c0c0c0;
    min-height: 20px;
    border-radius: 8px;
}
QTabBar::tab {
    background: #e0e0e0;
    color: #333333;
    padding: 6px 12px;
    border: 1px solid #d0d0d0;
    border-bottom: 1px solid #ffffff;
    border-radius: 4px 4px 0 0;
}
QTabBar::tab:selected {
    background: #ffffff;
    color: #333333;
    border: 1px solid #d0d0d0;
    border-bottom: 1px solid #ffffff;
    border-radius: 4px 4px 0 0;
    font-weight: bold;
}

QTabBar::tab:!selected {
    background: #f0f0f0;
}
QTabWidget::pane {
    border: 1px solid #d0d0d0;
    border-radius: 4px;
    background: #ffffff;
}
QMenu::item:disabled {
    background-color: #ffffff;
    color: #a0a0a0;
}
QAction:disabled {
    color: #a0a0a0;
}
)";

QString windowsStyleSheet = R"(
/* Minimal, modern-ish Windows look */
QWidget {
    font-family: "Segoe UI", "Inter", Tahoma, Verdana, Arial, sans-serif;
    font-size: 10pt;
    color: #111111;
    background-color: #f6f7f9;
}

QMenu {
    background-color: #ffffff;
    color: #111111;
    border: 1px solid #e5e7eb;
    border-radius: 10px;
    padding: 6px;
}

QMenu::item {
    background-color: transparent;
    color: #111111;
    padding: 8px 12px;
    border-radius: 8px;
}

QMenu::item:selected {
    background-color: #f3f4f6;
    color: #111111;
}

QMenu::item:disabled {
    color: #9ca3af;
}

QMenu::icon {
    margin-right: 10px;
}

QDialog, QFrame, QGroupBox {
    background-color: #ffffff;
    border: 1px solid #e5e7eb;
    border-radius: 12px;
}

QGroupBox {
    margin-top: 10px;
    padding-top: 12px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 6px;
    color: #374151;
}

QLabel {
    color: #111111;
}

QPushButton {
    background-color: #ffffff;
    color: #111111;
    border: 1px solid #d1d5db;
    border-radius: 10px;
    padding: 7px 12px;
}

QPushButton:hover {
    background-color: #f3f4f6;
}

QPushButton:pressed {
    background-color: #e5e7eb;
}

QPushButton:disabled {
    color: #9ca3af;
    border-color: #e5e7eb;
    background-color: #ffffff;
}

QLineEdit, QTextEdit, QPlainTextEdit, QComboBox, QSpinBox {
    background-color: #ffffff;
    color: #111111;
    border: 1px solid #d1d5db;
    border-radius: 10px;
    padding: 6px 10px;
    selection-background-color: #dbeafe;
}

QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus, QComboBox:focus, QSpinBox:focus {
    border: 1px solid #93c5fd;
}

QCheckBox, QRadioButton {
    color: #111111;
    spacing: 8px;
}

QTabWidget::pane {
    border: 1px solid #e5e7eb;
    border-radius: 12px;
    background: #ffffff;
}

QTabBar::tab {
    background: #f6f7f9;
    color: #374151;
    padding: 8px 12px;
    border: 1px solid #e5e7eb;
    border-bottom: none;
    border-top-left-radius: 10px;
    border-top-right-radius: 10px;
    margin-right: 4px;
}

QTabBar::tab:selected {
    background: #ffffff;
    color: #111111;
}

QScrollBar:vertical {
    border: none;
    background: transparent;
    width: 12px;
    margin: 2px 2px 2px 2px;
}

QScrollBar::handle:vertical {
    background: #d1d5db;
    min-height: 20px;
    border-radius: 6px;
}

QScrollBar::handle:vertical:hover {
    background: #c7cdd6;
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;
}

QSlider::groove:horizontal {
    border: 1px solid #e5e7eb;
    height: 8px;
    background: #ffffff;
    border-radius: 4px;
}

QSlider::handle:horizontal {
    background: #111111;
    border: 1px solid #e5e7eb;
    width: 16px;
    margin: -6px 0;
    border-radius: 8px;
}
)";

}  // namespace fptn::gui
