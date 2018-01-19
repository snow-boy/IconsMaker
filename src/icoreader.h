/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef ICOREADER_H
#define ICOREADER_H

#include <QImageIOHandler>

QT_BEGIN_NAMESPACE

// These next two structs represent how the icon information is stored
// in an ICO file.
typedef struct
{
    quint8  bWidth;               // Width of the image
    quint8  bHeight;              // Height of the image (times 2)
    quint8  bColorCount;          // Number of colors in image (0 if >=8bpp) [ not ture ]
    quint8  bReserved;            // Reserved
    quint16 wPlanes;              // Color Planes
    quint16 wBitCount;            // Bits per pixel
    quint32 dwBytesInRes;         // how many bytes in this resource?
    quint32 dwImageOffset;        // where in the file is this image
} ICONDIRENTRY, *LPICONDIRENTRY;
#define ICONDIRENTRY_SIZE 16

typedef struct
{
    quint16 idReserved;   // Reserved
    quint16 idType;       // resource type (1 for icons, 2 for cursors)
    quint16 idCount;      // how many images?
    ICONDIRENTRY    idEntries[1]; // the entries for each image
} ICONDIR, *LPICONDIR;
#define ICONDIR_SIZE    6       // Exclude the idEntries field

typedef struct {                    // BMP information header
    quint32 biSize;                // size of this struct
    quint32 biWidth;               // pixmap width
    quint32 biHeight;              // pixmap height     (specifies the combined height of the XOR and AND masks)
    quint16 biPlanes;              // should be 1
    quint16 biBitCount;            // number of bits per pixel
    quint32 biCompression;         // compression method
    quint32 biSizeImage;           // size of image
    quint32 biXPelsPerMeter;       // horizontal resolution
    quint32 biYPelsPerMeter;       // vertical resolution
    quint32 biClrUsed;             // number of colors used
    quint32 biClrImportant;        // number of important colors
} BMP_INFOHDR ,*LPBMP_INFOHDR;
#define BMP_INFOHDR_SIZE 40

class ICOReader
{
public:
    ICOReader(QIODevice * iodevice);
    int count();
    QImage iconAt(int index);
    static bool canRead(QIODevice *iodev);

    static QList<QImage> read(QIODevice * device);

    static bool write(QIODevice * device, const QList<QImage> & images);

private:
    bool readHeader();
    bool readIconEntry(int index, ICONDIRENTRY * iconEntry);

    bool readBMPHeader(quint32 imageOffset, BMP_INFOHDR * header);
    void findColorInfo(QImage & image);
    void readColorTable(QImage & image);

    void readBMP(QImage & image);
    void read1BitBMP(QImage & image);
    void read4BitBMP(QImage & image);
    void read8BitBMP(QImage & image);
    void read16_24_32BMP(QImage & image);

    struct IcoAttrib
    {
        int nbits;
        int ncolors;
        int h;
        int w;
        int depth;
    } icoAttrib;

    QIODevice * iod;
    qint64 startpos;
    bool headerRead;
    ICONDIR iconDir;

};

QT_END_NAMESPACE

#endif /* ICOREADER_H */

