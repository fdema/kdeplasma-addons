/*
 *   Copyright (C) 2007 Ivan Cukic <ivan.cukic+kde@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser/Library General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser/Library General Public License for more details
 *
 *   You should have received a copy of the GNU Lesser/Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QVariant>
#include "Widget.h"
#include "Global.h"
#include <KDebug>

namespace Lancelot {

WidgetCore::WidgetCore()
: m_group(NULL)
{
}

WidgetCore::~WidgetCore()
{
}

Widget::Widget(QString name, QGraphicsItem * parent) :
    WidgetCore(), Plasma::Widget(parent), m_hover(false), m_enabled(true),
    m_name(name)
{
    Instance::activeInstance()->addWidget(this);
    m_group = Instance::activeInstance()->defaultGroup();
}

Widget::~Widget()
{

}

void Widget::hoverEnterEvent ( QGraphicsSceneHoverEvent * event ) {
    if (!m_enabled) return;
    m_hover = true;
    Plasma::Widget::hoverEnterEvent(event);
    emit mouseHoverEnter();
    update();
}

void Widget::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ) {
    if (!m_enabled) return;
    m_hover = false;
    Plasma::Widget::hoverEnterEvent(event);
    emit mouseHoverLeave();
    update();
}

void Widget::setGroupByName(const QString & groupName)
{
    setGroup(instance()->group(groupName));
}

void Widget::setGroup(WidgetGroup * group)
{
    if (group == NULL) {
        group = instance()->defaultGroup();
    }

    if (group == m_group) return;

    if (m_group != NULL) {
        m_group->removeWidget(this);
    }

    m_group = group;
    m_group->addWidget(this);
    groupUpdated();
}

WidgetGroup * Widget::group()
{
    return m_group;
}

Instance * Widget::instance()
{
    if (!m_group) return Instance::activeInstance();
    
    return m_group->m_instance;
}

void Widget::groupUpdated()
{
    update();
}

QString Widget::name() const
{
    return m_name;
}

void Widget::setName(QString name)
{
    m_name = name;
}

void Widget::setGeometry(const QRectF & geometry)
{
    if (!m_group) //!instance()->processGeometryChanges)
        return;
    Plasma::Widget::setGeometry(geometry);
}

void Widget::update(const QRectF &rect)
{
    if (!m_group) //!instance()->processGeometryChanges)
        return;
    Plasma::Widget::update(rect);
}

void Widget::update(qreal x, qreal y, qreal w, qreal h)
{
    if (!m_group) //!instance()->processGeometryChanges)
        return;
    Plasma::Widget::update(x, y, w, h);
}

void Widget::paintWidget (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    paintBackground(painter);
}

void Widget::enable(bool value) {
    if (m_hover && m_enabled) {
        hoverLeaveEvent(NULL);
    }
    m_enabled = value;
}

void Widget::disable() {
    enable(false);
}

bool Widget::enabled() const {
    return m_enabled;
}

void Widget::paintBackground (QPainter * painter) {
    if (!m_group) return;

    QString element;
    if (!m_enabled) {
        element = "disabled";
    } else if (m_hover) {
        element = "active";
    } else {
        element = "normal";
    }

    paintBackground(painter, element);
}

void Widget::paintBackground (QPainter * painter, const QString & element) {
    if (!m_group) return;

    // Background Painting
    if (Plasma::Svg * svg = m_group->backgroundSvg()) {
        svg->resize(size());

        svg->paint(painter, 0, 0, element);

    } else if (const WidgetGroup::ColorScheme * scheme = m_group->backgroundColor()) {
        const QColor * color;
        if (!m_enabled) {
            color = & (scheme->disabled);
        } else if (m_hover) {
            color = & (scheme->active);
        } else {
            color = & (scheme->normal);
        }

        painter->fillRect(QRectF(QPointF(0, 0), size()), QBrush(*color));

    }

}

}

#include "Widget.moc"
