#include "fileutils.h"

#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QFileInfo>
#include <QFile>

bool emptyDirectory(const QString &path)
{
    QDir dir(path);

    if(!dir.exists())
    {
        qWarning() << "tried to empty non-existant dir" << path;
        return true;
    }

    bool success = true;
    // not empty -- we must empty it first
    QDirIterator di(dir.absolutePath(), QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    while (di.hasNext()) {
        di.next();
        const QFileInfo& fi = di.fileInfo();
        const QString &filePath = di.filePath();
        bool ok;
        if (fi.isDir() && !fi.isSymLink()) {
            ok = QDir(filePath).removeRecursively(); // recursive
        } else {
            ok = QFile::remove(filePath);
            if (!ok) { // Read-only files prevent directory deletion on Windows, retry with Write permission.
                const QFile::Permissions permissions = QFile::permissions(filePath);
                if (!(permissions & QFile::WriteUser))
                    ok = QFile::setPermissions(filePath, permissions | QFile::WriteUser)
                        && QFile::remove(filePath);
            }
        }
        if (!ok)
            success = false;
    }

    if(!success)
        qWarning() << "could not empty" << path;

    return success;
}
