/*
 * Copyright (c) 2021-2023 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <UI/Dashboard.h>
#include <Misc/TimerEvents.h>
#include <UI/DeclarativeWidget.h>

namespace UI
{
/**
 * @brief The DashboardWidget class
 *
 * The @c DashboardWidget class acts as a man-in-the-middle between the QML UI
 * and the C++ widgets. C++ widgets are loaded and initialized by this class,
 * and all the QML/Qt events are re-routed to the widgets using this class.
 * Finally, the C++ widget is "painted" on the QML interface in realtime,
 * effectively allowing us to use QWidget object directly in the QML user
 * interface.
 *
 * By using this approach, the QML user interface only needs to know the total
 * number of widgets and use the "global-index" approach to initialize every
 * widget using a Repeater item.
 *
 * On the other hand, this class figures out which widget should be loaded and
 * displayed in the user interface by knowing the "global-index" provider by the
 * QML Repeater.
 *
 * See the following files for more information:
 *      assets/qml/Dashboard/WidgetDelegate.qml
 *      assets/qml/Dashboard/WidgetLoader.qml
 *      assets/qml/Dashboard/WidgetGrid.qml
 */
class DashboardWidget : public DeclarativeWidget
{
  // clang-format off
  Q_OBJECT
  Q_PROPERTY(int widgetIndex
             READ widgetIndex
             WRITE setWidgetIndex
             NOTIFY widgetIndexChanged)
  Q_PROPERTY(int relativeIndex
             READ relativeIndex
             NOTIFY widgetIndexChanged)
  Q_PROPERTY(QString widgetIcon
             READ widgetIcon
             NOTIFY widgetIndexChanged)
  Q_PROPERTY(QString widgetTitle
             READ widgetTitle
             NOTIFY widgetIndexChanged)
  Q_PROPERTY(bool isExternalWindow
             READ isExternalWindow
             WRITE setIsExternalWindow
             NOTIFY isExternalWindowChanged)
  Q_PROPERTY(bool widgetVisible
             READ widgetVisible
             WRITE setVisible
             NOTIFY widgetVisibleChanged)
  Q_PROPERTY(bool isGpsMap
             READ isGpsMap
             NOTIFY widgetIndexChanged)
  Q_PROPERTY(qreal gpsAltitude
             READ gpsAltitude
             NOTIFY gpsDataChanged)
  Q_PROPERTY(qreal gpsLatitude
             READ gpsLatitude
             NOTIFY gpsDataChanged)
  Q_PROPERTY(qreal gpsLongitude
             READ gpsLongitude
             NOTIFY gpsDataChanged)
  // clang-format on

signals:
  void gpsDataChanged();
  void widgetIndexChanged();
  void widgetVisibleChanged();
  void isExternalWindowChanged();

public:
  DashboardWidget(QQuickItem *parent = 0);
  ~DashboardWidget();

  [[nodiscard]] int widgetIndex() const;
  [[nodiscard]] int relativeIndex() const;
  [[nodiscard]] bool widgetVisible() const;
  [[nodiscard]] QString widgetIcon() const;
  [[nodiscard]] QString widgetTitle() const;
  [[nodiscard]] bool isExternalWindow() const;
  [[nodiscard]] UI::Dashboard::WidgetType widgetType() const;

  [[nodiscard]] bool isGpsMap() const;
  [[nodiscard]] qreal gpsAltitude() const;
  [[nodiscard]] qreal gpsLatitude() const;
  [[nodiscard]] qreal gpsLongitude() const;

public slots:
  void setVisible(const bool visible);
  void setWidgetIndex(const int index);
  void setIsExternalWindow(const bool isWindow);

private slots:
  void updateWidgetVisible();

private:
  int m_index;
  bool m_isGpsMap;
  bool m_widgetVisible;
  bool m_isExternalWindow;
  QWidget *m_dbWidget;
};
} // namespace UI
