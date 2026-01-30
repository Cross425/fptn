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
/* Android TV inspired dark theme */
* {
    font-family: "Segoe UI";
    font-size: 12px;
    color: #E9EEF5;
}
QWidget {
    background: transparent;
}
QMenu {
    background-color: #131620;
    border: 1px solid #2A2F3D;
    border-radius: 10px;
    padding: 8px;
}
QMenu::item {
    padding: 8px 12px;
    border-radius: 8px;
    background: transparent;
}
QMenu::item:selected {
    background-color: #1C2232;
}
QMenu::item:disabled {
    color: #6E768A;
}
QLabel {
    color: #E9EEF5;
}
QPushButton {
    background-color: #1C2232;
    border: 1px solid #2A2F3D;
    border-radius: 10px;
    padding: 8px 12px;
}
QPushButton:hover {
    background-color: #232A3D;
}
QPushButton:pressed {
    background-color: #101521;
}
QLineEdit, QPlainTextEdit, QTextEdit {
    background-color: #0F121A;
    border: 1px solid #2A2F3D;
    border-radius: 10px;
    padding: 8px 10px;
    selection-background-color: #00C2FF;
}
QComboBox {
    background-color: #0F121A;
    border: 1px solid #2A2F3D;
    border-radius: 10px;
    padding: 8px 10px;
}
QComboBox::drop-down {
    border: 0px;
    width: 28px;
}
QComboBox QAbstractItemView {
    background-color: #131620;
    border: 1px solid #2A2F3D;
    border-radius: 10px;
    padding: 6px;
    outline: 0;
}
QCheckBox::indicator {
    width: 18px;
    height: 18px;
    border-radius: 5px;
    border: 1px solid #2A2F3D;
    background: #0F121A;
}
QCheckBox::indicator:checked {
    background: #00C2FF;
    border: 1px solid #00C2FF;
}
QGroupBox {
    border: 1px solid #2A2F3D;
    border-radius: 12px;
    margin-top: 10px;
    padding: 10px;
}
QGroupBox:title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 6px 0 6px;
    color: #B8C2D6;
}
QScrollBar:vertical {
    background: transparent;
    width: 10px;
    margin: 0px;
}
QScrollBar::handle:vertical {
    background: #2A2F3D;
    border-radius: 5px;
    min-height: 30px;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;
}

/* Mini widget */
#miniCard {
    background-color: #131620;
    border: 1px solid #2A2F3D;
    border-radius: 18px;
}
#miniTitle {
    font-size: 16px;
    font-weight: 700;
    color: #E9EEF5;
}
#miniState {
    font-size: 13px;
    color: #B8C2D6;
}
#miniLabel {
    font-size: 12px;
    color: #B8C2D6;
}
#miniInfo {
    font-size: 12px;
    color: #B8C2D6;
}
#miniPrimary {
    background-color: #00C2FF;
    border: 0px;
    color: #001018;
    font-weight: 700;
    border-radius: 12px;
}
#miniPrimary:hover {
    background-color: #25CDFF;
}
#miniPrimary:pressed {
    background-color: #00A6DA;
}
#miniClose {
    background: transparent;
    border: 1px solid #2A2F3D;
    border-radius: 10px;
    color: #B8C2D6;
    font-weight: 700;
}
#miniClose:hover {
    background-color: #1C2232;
}
)";

}  // namespace fptn::gui
