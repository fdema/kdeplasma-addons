/***************************************************************************
 *   Copyright (C) 2007 by Tobias Koenig <tokoe@kde.org>                   *
 *   Copyright (C) 2008-2010 Matthias Fuchs <mat69@gmx.net>                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include "ui_appearanceSettings.h"
#include "ui_advancedsettings.h"
#include "ui_comicSettings.h"

#include <QtGui/QWidget>
#include <QTime>

class ComicModel;
class KConfigDialog;
class QCheckBox;
class QComboBox;
class QSortFilterProxyModel;
class QPushButton;

namespace KNS3 {
    class DownloadDialog;
}

namespace Plasma {
    class DataEngine;
}

class ConfigWidget : public QWidget
{
        Q_OBJECT
    public:
        ConfigWidget( Plasma::DataEngine *engine, ComicModel *model, const QStringList &usedComics, QSortFilterProxyModel *proxy, KConfigDialog *parent );
        ~ConfigWidget();

        void setShowComicUrl( bool show );
        bool showComicUrl() const;
        void setShowComicAuthor( bool show );
        bool showComicAuthor() const;
        void setShowComicTitle( bool show );
        bool showComicTitle() const;
        void setShowComicIdentifier( bool show );
        bool showComicIdentifier() const;
        void setShowErrorPicture( bool show );
        bool showErrorPicture() const;
        void setArrowsOnHover( bool arrows );
        bool arrowsOnHover() const;
        void setMiddleClick( bool checked );
        bool middleClick() const;
        void setTabSwitchTime( const QTime &time );
        QTime tabSwitchTime() const;
        void setHideTabBar( bool hide );
        bool hideTabBar() const;
        void setUseTabs( bool use );
        bool useTabs() const;
        void setSwitchTabs( bool switchTabs );
        bool switchTabs() const;
        void setTabView( int tabView );
        int tabView() const;
        bool useMaxComicLimit() const;
        void setUseMaxComicLimit( bool use );
        int maxComicLimit() const;
        void setMaxComicLimit( int limit );

        QWidget *comicSettings;
        QWidget *appearanceSettings;
        QWidget *advancedSettings;

    Q_SIGNALS:
        void maxSizeClicked();
        void enableApply();

    protected slots:
        void getNewStuff();
        void newStuffFinished();

    private slots:
        void slotComboBoxChosen();
        void slotListChosen();
        void slotSave();

    private:
        void checkCurrentIndex();

    private:
        Ui::ComicSettings comicUi;
        Ui::AppearanceSettings appearanceUi;
        Ui::AdvancedSettings advancedUi;
        Plasma::DataEngine *mEngine;
        ComicModel *mModel;
        QSortFilterProxyModel *mProxyModel;
        KNS3::DownloadDialog* mNewStuffDialog;
};

#endif
