#include "hexray.h"
#include <fstream>
#include <sstream>
#include <iomanip>


HexRay::HexRay()
{
}

HexRay::~HexRay()
{
}

/**
 * Open the file in binary mode and return its content
 */
std::vector<char> HexRay::get_raw(std::string input_file_path)
{
    std::ifstream file(input_file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        return {};
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

void HexRay::build_head_line(wxTextCtrl& ctrl)
{
    std::stringstream line;

    line << "  Offset   ";  // add the initial padding
    for (size_t i = 0; i < HEXRAY_COLS; ++i)
    {
        // Force the hex formatting for the current index
        line << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << i;

        // Add a space between bytes, but not after the last one
        if (i < (HEXRAY_COLS-1)) {
            if (i == (HEXRAY_COLS/2-1))
            {
                line << " - ";
            }
            else
            {
                line << " ";
            }
        }
    }

    // Update the wxWidgets control
    ctrl.Clear();
    ctrl.AppendText(wxString(line.str()));
    ctrl.Show(true);
}

void HexRay::update_dump(wxTextCtrl& ctrl, const std::vector<char>& raw_buffer)
{
    size_t raw_buffer_sz = raw_buffer.size();

    ctrl.Clear();
    for (size_t offset = 0; offset < raw_buffer_sz; offset += HEXRAY_COLS)
    {
        unsigned int val32 = static_cast<unsigned int>(offset);
        wxString line = wxString::Format("%04X_%04X  ", (val32 >> 16), (val32 & 0xFFFF));
        wxString ascii;

        for (size_t i = 0; i < HEXRAY_COLS; ++i)
        {
            const size_t index = offset + i;

            if (index < raw_buffer_sz)
            {
                const unsigned char byte = static_cast<unsigned char>(raw_buffer[index]);
                line << wxString::Format("%02X ", byte);
                ascii << (std::isprint(byte) ? static_cast<char>(byte) : '.');
                if (i == (HEXRAY_COLS/2-1))
                {
                    line << "- ";
                    ascii << ' ';
                }
            }
            else
            {
                if (i == (HEXRAY_COLS/2-1))
                {
                    line << "     ";
                    ascii << "  ";
                }
                else
                {
                    line << "   ";
                    ascii << ' ';
                }
            }
        }

        line << "  " << ascii;
        ctrl.AppendText(line + "\n");
    }
    ctrl.Show(true);
}
