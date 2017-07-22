/*
 * This file is part of the mouse gesture package.
 * Copyright (C) 2006 Johan Thelin <e8johan@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the
 * following conditions are met:
 *
 *   - Redistributions of source code must retain the above
 *     copyright notice, this list of conditions and the
 *     following disclaimer.
 *   - Redistributions in binary form must reproduce the
 *     above copyright notice, this list of conditions and
 *     the following disclaimer in the documentation and/or
 *     other materials provided with the distribution.
 *   - The names of its contributors may be used to endorse
 *     or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <QApplication>

#include "mainwindow.h"

#include "MouseGestureFilter.h"
#include "MouseGesture.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    MouseGestureFilter filter;
    MainWindow mw;

    MouseGesture *g;
    DirectionList dl;

    /* Clear all by three sideways moves */
    dl << AnyHorizontal << AnyHorizontal << AnyHorizontal;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(clearAll()) );

    /* Set all by moving up-left */
    dl.clear();
    dl << Up << Left;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(setAll()) );

    /* When nothing else matches */
    dl.clear();
    dl << NoMatch;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(noMatch()) );

    /* The secret message - four possible starting corners */
    dl.clear();
    dl << Up << Right << Down << Left;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(rectMessage()) );

    dl.clear();
    dl << Right << Down << Left << Up;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(rectMessage()) );

    dl.clear();
    dl << Down << Left << Up << Right ;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(rectMessage()) );

    dl.clear();
    dl << Left << Up << Right << Down;
    g = new MouseGesture( dl, &filter );
    filter.addGesture( g );
    mw.connect( g, SIGNAL(gestured()), SLOT(rectMessage()) );

    mw.installEventFilter( &filter );
    mw.show();

    return app.exec();
}
