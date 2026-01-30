/*=============================================================================
Copyright (c) 2024-2025 Stas Skokov

Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/

#pragma once

#include <QComboBox>    // NOLINT(build/include_order)
#include <QElapsedTimer>// NOLINT(build/include_order)
#include <QFrame>       // NOLINT(build/include_order)
#include <QLabel>       // NOLINT(build/include_order)
#include <QPushButton>  // NOLINT(build/include_order)
#include <QTcpSocket>   // NOLINT(build/include_order)
#include <QTimer>       // NOLINT(build/include_order)
#include <QWidget>      // NOLINT(build/include_order)

#include "gui/settingsmodel/settingsmodel.h"
#include "gui/speedwidget/speedwidget.h"
#include "utils/speed_estimator/server_info.h"

namespace fptn::gui {

class TrayApp;

class MiniWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MiniWidget(TrayApp* tray_app,
      const SettingsModelPtr& settings,
      QWidget* parent = nullptr);

  void RefreshServerList();
  void SetStateText(const QString& text);
  void SetConnectedServerText(const QString& text);

  void SetConnected(bool connected);

  void UpdateSpeed(std::size_t rx_bps, std::size_t tx_bps);

  void UpdatePingTarget(const QString& host, int port);

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 private:
  void BuildUi();
  void StartPing();
  void StopPing();
  void OnPingTimeout();
  void ApplyWindowFlags();

 private:
  TrayApp* tray_app_ = nullptr;
  SettingsModelPtr settings_;

  QFrame* card_ = nullptr;
  QLabel* title_label_ = nullptr;
  QLabel* state_label_ = nullptr;
  QLabel* server_label_ = nullptr;

  QComboBox* server_combo_ = nullptr;
  QPushButton* toggle_button_ = nullptr;
  QPushButton* close_button_ = nullptr;

  QLabel* ping_label_ = nullptr;
  SpeedWidget* speed_widget_ = nullptr;

  QTimer* ping_timer_ = nullptr;
  QTcpSocket* ping_socket_ = nullptr;
  QElapsedTimer ping_elapsed_;

  QString ping_host_;
  int ping_port_ = 0;

  bool is_connected_ = false;

  QPoint drag_pos_;
};

}  // namespace fptn::gui
