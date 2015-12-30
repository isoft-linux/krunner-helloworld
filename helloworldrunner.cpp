/*
 *   Copyright (C) 2006 Aaron Seigo <aseigo@kde.org>
 *   Copyright (C) 2014 Vishesh Handa <vhanda@kde.org>
 *   Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "helloworldrunner.h"

#include <QMimeData>
#include <QIcon>
#include <QDebug>
#include <QUrl>
#include <QMessageBox>

#include <KLocalizedString>

HelloworldRunner::HelloworldRunner(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args)

    setObjectName(QLatin1String("Helloworld"));
    setPriority(AbstractRunner::HighestPriority);

    addSyntax(Plasma::RunnerSyntax(":q:", i18n("Echo hello to :q:")));
}

HelloworldRunner::~HelloworldRunner()
{
}

QStringList HelloworldRunner::categories() const
{
    QStringList cat;
    cat << i18n("Helloworld");

    return cat;
}

QIcon HelloworldRunner::categoryIcon(const QString& category) const
{
    if (category == i18n("Helloworld"))
        return QIcon::fromTheme("text-x-c++src");

    return Plasma::AbstractRunner::categoryIcon(category);
}


void HelloworldRunner::match(Plasma::RunnerContext &context)
{
    const QString term = context.query();
    QList<Plasma::QueryMatch> matches;
    QSet<QString> seen;
    Plasma::QueryMatch match(this);
    match.setType(Plasma::QueryMatch::ExactMatch);
    setupMatch(term, match);
    match.setRelevance(1);
    matches << match;
    seen.insert("hello " + term);
    seen.insert("hello " + term);
    if (!context.isValid())
        return;
    context.addMatches(matches);
}

void HelloworldRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);
    QMessageBox box;
    box.setText("Hello " + match.data().toString());
    box.exec();
}

void HelloworldRunner::setupMatch(const QString &term, Plasma::QueryMatch &match)
{
    match.setText("hello " + term);
    match.setData("hello " + term);
    match.setSubtext("hello " + term);
    match.setIcon(QIcon::fromTheme("text-x-c++src"));
}

QMimeData *HelloworldRunner::mimeDataForMatch(const Plasma::QueryMatch &match) 
{
    QMimeData *result = new QMimeData();
    QList<QUrl> urls;
    urls << QUrl("hello://" + match.data().toString());
    result->setUrls(urls);
    return result;
}

K_EXPORT_PLASMA_RUNNER(helloworld, HelloworldRunner)

#include "helloworldrunner.moc"

