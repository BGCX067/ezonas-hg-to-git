/**
 * Copyright (c) 2010-2010 Nigel Atkinson
 *
 * This software is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "gorillaexporter.h"
#include "../fontconfig.h"

GorillaExporter::GorillaExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("gorilla");
}


bool GorillaExporter::Export(QByteArray& out)
{
    typedef QMap<ushort,int>::ConstIterator Kerning;

    const Symbol& first = symbols().front();
    const Symbol& last = symbols().back();

    const Symbol& space = symbols()[ ' ' - first.id ];
    const Symbol& w = symbols()[ 'W' - first.id ];
    const int ascender = metrics().ascender;


    out.append( QString( "[Font.%1]\n").arg( fontConfig()->size() ) );
    out.append( QString( "lineheight %1\n").arg( metrics().height ));
    out.append( QString( "spacelength %1\n").arg( space.advance ));
    out.append( QString( "baseline %1\n").arg( ascender ));
    out.append( QString( "monowidth %1\n").arg( w.advance ));
    out.append( QString( "letterspacing %1\n").arg( fontConfig()->charSpacing()));
    out.append( QString( "range %1 %2\n").arg( first.id ).arg( last.id ) );

    foreach( const Symbol& c, symbols())
    {
        out.append( QString( "glyph_%1 %2 %3 %4 %5 %6\n")
                    .arg( c.id )
                    .arg( c.placeX - c.offsetX )
                    .arg( c.placeY - ( ascender - c.offsetY ) )
                    .arg( c.placeW + c.offsetX )
                    .arg( c.placeH + ( ascender - c.offsetY ))
                    .arg( c.advance )
                    );
    }
    foreach( const Symbol& c, symbols())
    {
        for( Kerning k = c.kerning.begin(); k != c.kerning.end(); k++ )
        {
            out.append( QString( "kerning_%2 %1 %3\n")
                        .arg( c.id )
                        .arg( k.key() )
                        .arg( k.value() )
                        );
        }
    }

    return true;
}


AbstractExporter* GorillaExporterFactoryFunc (QObject* parent) {
    return new GorillaExporter(parent);
}

