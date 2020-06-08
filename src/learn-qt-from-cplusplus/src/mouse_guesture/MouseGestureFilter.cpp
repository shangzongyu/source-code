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

#include "MouseGestureFilter.h"
#include "MouseGesture.h"

#include "mousegesturerecognizer.h"

/*
 *  Internal support class to bridge the
 *  toolkit independent mouse gesture
 *  recognizer and the Qt specific
 *  implementation.
 */
class GestureCallbackToSignal : public Gesture::MouseGestureCallback
{
public:
    GestureCallbackToSignal( MouseGesture *object )
    {
        m_object = object;
    }

    void callback()
    {
        m_object->emitGestured();
    }

private:
    MouseGesture *m_object;
};

typedef QList<GestureCallbackToSignal> BridgeList;

/*
 *  Private members of the MouseGestureFilter class
 */
class MouseGestureFilter::Private
{
public:
    Qt::MouseButton gestureButton;
    bool tracing;

    Gesture::MouseGestureRecognizer mgr;
    BridgeList bridges;
};

/**********************************************************/

MouseGestureFilter::MouseGestureFilter( Qt::MouseButton gestureButton, QObject *parent ) : QObject( parent )
{
    d = new Private;

    d->gestureButton = gestureButton;
    d->tracing = false;
}

MouseGestureFilter::~MouseGestureFilter()
{
    delete d;
}

/*
 *  Converts the DirectionList to a Gesture::DirecionList,
 *  creates a bridge and adds the gesture to the recognizer.
 */
void MouseGestureFilter::addGesture( MouseGesture *gesture )
{
    Gesture::DirectionList dl;

    for( DirectionList::const_iterator source = gesture->directions().begin(); source != gesture->directions().end(); ++source )
        dl.push_back( *source );

    d->bridges.append( GestureCallbackToSignal( gesture ) );
    d->mgr.addGestureDefinition( Gesture::GestureDefinition( dl, &(d->bridges[ d->bridges.size()-1 ]) ) );
}

void MouseGestureFilter::clearGestures( )
{
    d->bridges.clear();
    d->mgr.clearGestureDefinitions();
}

bool MouseGestureFilter::eventFilter( QObject *obj, QEvent *event )
{
    switch( event->type() )
    {
    case QEvent::MouseButtonPress:
        if( mouseButtonPressEvent( obj, dynamic_cast<QMouseEvent*>(event) ) )
            return true;

        break;

    case QEvent::MouseButtonRelease:
        if( mouseButtonReleaseEvent( obj, dynamic_cast<QMouseEvent*>(event) ) )
            return true;

        break;

    case QEvent::MouseMove:
        if( mouseMoveEvent( obj, dynamic_cast<QMouseEvent*>(event) ) )
            return true;

        break;

    default:
        break;
    }

    return QObject::eventFilter( obj, event );
}

bool MouseGestureFilter::mouseButtonPressEvent( QObject *obj, QMouseEvent *event )
{
    if( event->button() == d->gestureButton )
    {
        d->mgr.startGesture( event->pos().x(), event->pos().y() );
        d->tracing = true;

        return true;
    }
    else
        return false;
}

bool MouseGestureFilter::mouseButtonReleaseEvent( QObject *obj, QMouseEvent *event )
{
    if( d->tracing && event->button() == d->gestureButton )
    {
        d->mgr.endGesture( event->pos().x(), event->pos().y() );
        d->tracing = false;

        return true;
    }
    else
        return false;
}

bool MouseGestureFilter::mouseMoveEvent( QObject *obj, QMouseEvent *event )
{
    if( d->tracing )
    {
        d->mgr.addPoint( event->pos().x(), event->pos().y() );

        return true;
    }
    else
        return false;
}
