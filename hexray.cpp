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

void HexRay::build_head_line(wxTextCtrl& ctrl, int step)
{
    std::string blanks(1 + (step-1)*2, ' '); 
    std::stringstream line;

    line << "  Offset   ";  // add the initial padding
    for (size_t i = 0; i < HEXRAY_COLS; i += step)
    {
        // 1. Format the current index as a 2-character uppercase hex
        line << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << i;

        // 2. Determine if there is a next element in the sequence
        // otherwise don't add spaces between bytes
        if (i + step < HEXRAY_COLS)
        {
            line << blanks;
            // 3. Determine the position of the "midpoint" separator
            if (i == (HEXRAY_COLS/2-step))
            {
                if (step == 1)
                {
                    line << "- ";  // use a dash
                }
                else
                {
                    line << "  ";  // use a blank
                }
            }
        }
    }

    // Update the wxWidgets control
    ctrl.Clear();
    ctrl.AppendText(wxString(line.str()));
    ctrl.Show(true);
}

void HexRay::update_dump(wxTextCtrl& ctrl, const std::vector<char>& raw_buffer, int step)
{
    // Sanity check for step width (default to 1 byte if invalid)
    if (step != 1 && step != 2 && step != 4)
    {
        step = 1;
    }

    // Format specifier: step * 2 characters (2 hex digits per byte) plus trailing space
    wxString word_width = wxString::Format("%%0%dX ", step * 2);
    size_t raw_buffer_sz = raw_buffer.size();

    ctrl.Clear();

    // Wrapping ctrl.Freeze() and ctrl.Thaw() around the processing loop.
    // This prevents wxTextCtrl from repainting line-by-line, reducing UI lag during buffer updates.

    ctrl.Freeze(); // Freeze UI rendering to prevent flickering during mass updates

    for (size_t offset = 0; offset < raw_buffer_sz; offset += HEXRAY_COLS)
    {
        unsigned int val32 = static_cast<unsigned int>(offset);
        wxString line = wxString::Format("%04X_%04X  ", (val32 >> 16), (val32 & 0xFFFF));
        wxString ascii;

        for (size_t i = 0; i < HEXRAY_COLS; i += step)
        {
            const size_t index = offset + i;

            if (index < raw_buffer_sz)
            {
                // 1. Reconstruct multi-byte word (Little-Endian)
                unsigned int word_val = 0;
                size_t bytes_read = 0;

                for (int b = 0; b < step && (index + b) < raw_buffer_sz; ++b)
                {
                    const unsigned char byte = static_cast<unsigned char>(raw_buffer[index + b]);
                    word_val |= (static_cast<unsigned int>(byte) << (b * 8));
                    
                    // Build ASCII representation byte-by-byte
                    ascii << (std::isprint(byte) ? static_cast<char>(byte) : '.');
                    bytes_read++;
                }

                // If a full word was read, format it; otherwise pad appropriately
                if (bytes_read == static_cast<size_t>(step))
                {
                    line << wxString::Format(word_width, word_val);
                }
                else
                {
                    // Partial word at the end of buffer: pad hex section
                    line << wxString(' ', step * 2 + 1);
                }

                // Midpoint separator logic
                if (i == (HEXRAY_COLS / 2 - step))
                {
                    line << "- ";
                    ascii << ' ';
                }
            }
            else
            {
                // 2. Trailing blanks for completely empty slots
                line << wxString(' ', step * 2 + 1);
                ascii << wxString(' ', step);

                if (i == (HEXRAY_COLS / 2 - step))
                {
                    line << "  "; // Match length of "- "
                    ascii << ' ';
                }
            }
        }

        line << "  " << ascii;
        ctrl.AppendText(line + "\n");
    }

    ctrl.Thaw(); // Resume window painting
    ctrl.Show(true);
}

int HexRay::get_step_size(int index)
{
    int step_size;

    switch(index)
    {
        case 0:
        step_size = 1;
        break;
        
        case 1:
        step_size = 2;
        break;
        
        case 2:
        step_size = 4;
        break;

        default:
        step_size = HEXRAY_DEF_STEPS;
    }

    return step_size;
}
