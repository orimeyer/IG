// pgm_writer.h
#ifndef PGM_WRITER_H
#define PGM_WRITER_H

#include <vector>
#include <string>

bool save_pgm(const std::string& filename, const std::vector<std::vector<double>>& data);

#endif // PGM_WRITER_H
