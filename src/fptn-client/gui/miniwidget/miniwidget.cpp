/*=============================================================================
Copyright (c) 2024-2025 Stas Skokov

Distributed under the MIT License (https://opensource.org/licenses/MIT)
=============================================================================*/

#include "gui/miniwidget/miniwidget.h"

#include <QApplication>              // NOLINT(build/include_order)
#include <QGraphicsDropShadowEffect> // NOLINT(build/include_order)
#include <QHBoxLayout>               // NOLINT(build/include_order)
#include <QMouseEvent>               // NOLINT(build/include_order)
#include <QVBoxLayout>               // NOLINT(build/include_order)

#include "gui/tray/tray.h"

using fptn::gui::MiniWidget;

namespace {

QString HumanServerName(const fptn::gui::ServerConfig& s,
    const fptn::gui::ServiceConfig& svc) {
  if (!svc.service_name.isEmpty()) {
    return svc.service_name + " — " + s.name;
  }
  return s.name;
}

}  // namespace

MiniWidget::MiniWidget(TrayApp* tray_app,
    const SettingsModelPtr& settings,
    QWidget* parent)
    : QWidget(parent), tray_app_(tray_app), settings_(settings) {
  ApplyWindowFlags();
  BuildUi();
  RefreshServerList();

  ping_timer_ = new QTimer(this);
  ping_timer_->setInterval(5000);
  connect(ping_timer_, &QTimer::timeout, this, &MiniWidget::OnPingTimeout);

  ping_socket_ = new QTcpSocket(this);
  connect(ping_socket_, &QTcpSocket::connected, this, [this]() {
    const qint64 ms = ping_elapsed_.elapsed();
    ping_label_->setText(QObject::tr("Ping: %1 ms").arg(ms));
    ping_socket_->abort();
  });
  connect(ping_socket_, &QTcpSocket::errorOccurred, this, [this](auto) {
    // If cannot connect, show dash (avoid noisy errors).
    ping_label_->setText(QObject::tr("Ping: —"));
    ping_socket_->abort();
  });
}

void MiniWidget::ApplyWindowFlags() {
  setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setAttribute(Qt::WA_TranslucentBackground, true);
}

void MiniWidget::BuildUi() {
  auto* root = new QVBoxLayout(this);
  root->setContentsMargins(12, 12, 12, 12);
  root->setSpacing(0);

  card_ = new QFrame(this);
  card_->setObjectName("miniCard");
  card_->setMinimumWidth(360);

  auto* shadow = new QGraphicsDropShadowEffect(card_);
  shadow->setBlurRadius(28);
  shadow->setOffset(0, 10);
  card_->setGraphicsEffect(shadow);

  auto* card_layout = new QVBoxLayout(card_);
  card_layout->setContentsMargins(16, 16, 16, 16);
  card_layout->setSpacing(12);

  // Header
  auto* header = new QHBoxLayout();
  header->setSpacing(10);

  title_label_ = new QLabel(QObject::tr("FPTN"), card_);
  title_label_->setObjectName("miniTitle");

  close_button_ = new QPushButton(QString::fromUtf8("✕"), card_);
  close_button_->setObjectName("miniClose");
  close_button_->setFixedSize(30, 30);
  connect(close_button_, &QPushButton::clicked, this, &QWidget::hide);

  header->addWidget(title_label_);
  header->addStretch();
  header->addWidget(close_button_);
  card_layout->addLayout(header);

  // State row
  state_label_ = new QLabel(QObject::tr("Disconnected"), card_);
  state_label_->setObjectName("miniState");
  card_layout->addWidget(state_label_);

  // Server row
  server_label_ = new QLabel(QObject::tr("Server"), card_);
  server_label_->setObjectName("miniLabel");

  server_combo_ = new QComboBox(card_);
  server_combo_->setObjectName("miniCombo");

  auto* server_row = new QVBoxLayout();
  server_row->setSpacing(6);
  server_row->addWidget(server_label_);
  server_row->addWidget(server_combo_);
  card_layout->addLayout(server_row);

  // Ping + speed
  ping_label_ = new QLabel(QObject::tr("Ping: —"), card_);
  ping_label_->setObjectName("miniInfo");

  speed_widget_ = new fptn::gui::SpeedWidget(card_);
  speed_widget_->setObjectName("miniSpeed");
  speed_widget_->UpdateSpeed(0, 0);

  auto* info_row = new QHBoxLayout();
  info_row->addWidget(ping_label_);
  info_row->addStretch();
  info_row->addWidget(speed_widget_);
  card_layout->addLayout(info_row);

  // Toggle button
  toggle_button_ = new QPushButton(QObject::tr("Connect"), card_);
  toggle_button_->setObjectName("miniPrimary");
  toggle_button_->setMinimumHeight(44);

  connect(toggle_button_, &QPushButton::clicked, this, [this]() {
    if (!tray_app_) return;

    if (is_connected_) {
      tray_app_->RequestDisconnect();
      return;
    }

    // Resolve selection to a ServerInfo and connect.
    const int idx = server_combo_->currentIndex();
    if (idx < 0) {
      tray_app_->RequestSmartConnect();
      return;
    }

    // We store (serviceIndex, serverIndex, limitedZone) in item data.
    const QVariant data = server_combo_->currentData();
    if (!data.isValid()) {
      tray_app_->RequestSmartConnect();
      return;
    }

    const QString packed = data.toString();
    const auto parts = packed.split(":");
    if (parts.size() != 3) {
      tray_app_->RequestSmartConnect();
      return;
    }
    const int service_idx = parts[0].toInt();
    const int server_idx = parts[1].toInt();
    const bool limited = (parts[2] == "1");

    tray_app_->RequestConnectFromSettings(service_idx, server_idx, limited);
  });

  card_layout->addWidget(toggle_button_);

  root->addWidget(card_);
}

void MiniWidget::RefreshServerList() {
  server_combo_->clear();

  // First item: Smart connect
  server_combo_->addItem(QObject::tr("Smart connect"), "smart");

  const auto services = settings_ ? settings_->Services() : QVector<ServiceConfig>{};
  for (int si = 0; si < services.size(); ++si) {
    const auto& svc = services[si];

    // Normal servers
    for (int vi = 0; vi < svc.servers.size(); ++vi) {
      const auto& srv = svc.servers[vi];
      const QString name = HumanServerName(srv, svc);
      server_combo_->addItem(name, QString("%1:%2:%3").arg(si).arg(vi).arg(0));
    }

    // Limited zone servers
    for (int vi = 0; vi < svc.censored_zone_servers.size(); ++vi) {
      const auto& srv = svc.censored_zone_servers[vi];
      const QString name =
          HumanServerName(srv, svc) + " (" + QObject::tr("limited") + ")";
      server_combo_->addItem(name, QString("%1:%2:%3").arg(si).arg(vi).arg(1));
    }
  }
}

void MiniWidget::SetStateText(const QString& text) {
  state_label_->setText(text);
}

void MiniWidget::SetConnectedServerText(const QString& text) {
  // Reuse state row for compactness
  if (text.isEmpty()) return;
  state_label_->setText(text);
}

void MiniWidget::SetConnected(bool connected) {
  is_connected_ = connected;
  toggle_button_->setText(is_connected_ ? QObject::tr("Disconnect")
                                       : QObject::tr("Connect"));
}

void MiniWidget::UpdateSpeed(std::size_t rx_bps, std::size_t tx_bps) {
  if (speed_widget_) speed_widget_->UpdateSpeed(rx_bps, tx_bps);
}

void MiniWidget::UpdatePingTarget(const QString& host, int port) {
  ping_host_ = host;
  ping_port_ = port;
  StartPing();
}

void MiniWidget::StartPing() {
  if (ping_host_.isEmpty() || ping_port_ <= 0) {
    StopPing();
    ping_label_->setText(QObject::tr("Ping: —"));
    return;
  }
  if (!ping_timer_->isActive()) ping_timer_->start();
  OnPingTimeout();  // immediate
}

void MiniWidget::StopPing() {
  if (ping_timer_ && ping_timer_->isActive()) ping_timer_->stop();
  if (ping_socket_) ping_socket_->abort();
}

void MiniWidget::OnPingTimeout() {
  if (ping_host_.isEmpty() || ping_port_ <= 0) return;

  // Use TCP handshake time as a practical "ping" (works without ICMP permissions).
  ping_elapsed_.restart();
  ping_socket_->abort();
  ping_socket_->connectToHost(ping_host_, static_cast<quint16>(ping_port_));
}

void MiniWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    drag_pos_ = event->globalPosition().toPoint() - frameGeometry().topLeft();
    event->accept();
  }
  QWidget::mousePressEvent(event);
}

void MiniWidget::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    move(event->globalPosition().toPoint() - drag_pos_);
    event->accept();
  }
  QWidget::mouseMoveEvent(event);
}
