// pgm_writer.h
#ifndef PGM_WRITER_H
#define PGM_WRITER_H

#include <vector>
#include <string>

// שמירת מטריצה דו־ממדית של ערכים (0-255) לקובץ PGM (גווני אפור)
// מחזיר true אם הצליח
bool save_pgm(const std::string& filename, const std::vector<std::vector<double>>& data);

#endif // PGM_WRITER_H
