/*
 * Copyright (c) 2014-2019 Meltytech, LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COLORPICKERITEM_H
#define COLORPICKERITEM_H

#include <QColor>
#include <QObject>

class ColorPickerItem : public QObject {
    Q_OBJECT
public:
    explicit ColorPickerItem(QObject* parent = nullptr);

signals:
    void pickColor();
    void colorPicked(const QColor &color);
    void cancelled();

private slots:
    void startPick();
};

#endif // COLORPICKERITEM_H
