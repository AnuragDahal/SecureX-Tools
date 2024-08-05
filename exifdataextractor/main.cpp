#include <iostream>
#include <iomanip>
#include <fstream>
#include <libexif/exif-data.h>
#include <cstring> // For std::strlen

void print_tag(ExifEntry *entry, std::ofstream &output_file)
{
    char buf[1024];
    const int name_width = 30; 

    if (entry)
    {
        exif_entry_get_value(entry, buf, sizeof(buf));
        std::string tag_name = exif_tag_get_name(entry->tag);
        std::string tag_value = (*buf) ? buf : "<no data>";

        output_file << std::left << std::setw(name_width) << tag_name
                   << ": " << tag_value << std::endl;
    }
}

void write_exif_data_to_bin(ExifData *exif_data, std::ofstream &output_file)
{
    // Write EXIF data to binary file
    for (int i = 0; i < EXIF_IFD_COUNT; i++)
    {
        ExifContent *content = exif_data->ifd[i];
        if (content)
        {
            for (unsigned int j = 0; j < content->count; j++)
            {
                ExifEntry *entry = content->entries[j];
                if (entry)
                {
                    // Write tag ID
                    uint16_t tag_id = entry->tag;
                    output_file.write(reinterpret_cast<const char*>(&tag_id), sizeof(tag_id));

                    // Write tag data
                    char buf[1024];
                    exif_entry_get_value(entry, buf, sizeof(buf));
                    size_t data_length = std::strlen(buf);
                    output_file.write(reinterpret_cast<const char*>(&data_length), sizeof(data_length));
                    output_file.write(buf, data_length);
                }
            }
        }
    }
}

void read_exif_data(const char *file_name, const std::string &file_type)
{
    ExifData *exif_data = exif_data_new_from_file(file_name);
    if (!exif_data)
    {
        std::cerr << "No EXIF data found in file " << file_name << std::endl;
        return;
    }

    std::string output_file_name = "exif_data." + file_type;
    std::ofstream output_file(output_file_name, std::ios::binary);

    if (!output_file.is_open())
    {
        std::cerr << "Failed to open file " << output_file_name << " for writing." << std::endl;
        exif_data_unref(exif_data);
        return;
    }

    if (file_type == "html")
    {
        output_file << "<html><head><style>" << std::endl;
        output_file << "body { font-family: Arial, sans-serif; margin: 20px; }" << std::endl;
        output_file << "table { width: 100%; border-collapse: collapse; margin-top: 20px; }" << std::endl;
        output_file << "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }" << std::endl;
        output_file << "th { background-color: #f4f4f4; }" << std::endl;
        output_file << "tr:nth-child(even) { background-color: #f9f9f9; }" << std::endl;
        output_file << "h1 { color: #333; }" << std::endl;
        output_file << "div { display: flex; justify-content: center; align-items: center; margin: 20px 0; }" << std::endl;
        output_file << "img { max-width: 100%; height: 512px; border: 2px solid #ddd; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.2); }" << std::endl;
        output_file << "</style></head><body>" << std::endl;
        output_file << "<h1>EXIF data for file: " << file_name << "</h1>" << std::endl;

        // Wrap the image in a div to center it
        output_file << "<div><img src='./sample.jpg' alt='Image' /></div>" << std::endl;
        output_file << "<table><tr><th>Tag Name</th><th>Value</th></tr>" << std::endl;

        // Write EXIF data to HTML
        for (int i = 0; i < EXIF_IFD_COUNT; i++)
        {
            ExifContent *content = exif_data->ifd[i];
            if (content)
            {
                for (unsigned int j = 0; j < content->count; j++)
                {
                    char buf[1024];
                    exif_entry_get_value(content->entries[j], buf, sizeof(buf));
                    std::string tag_name = exif_tag_get_name(content->entries[j]->tag);
                    std::string tag_value = (*buf) ? buf : "<no data>";
                    output_file << "<tr><td>" << tag_name << "</td><td>" << tag_value << "</td></tr>" << std::endl;
                }
            }
        }

        output_file << "</table></body></html>" << std::endl;
    }
    else if (file_type == "bin")
    {
        // Write EXIF data to binary file
        write_exif_data_to_bin(exif_data, output_file);
    }
    else
    {
        output_file << "EXIF data for file: " << file_name << std::endl;
        output_file << std::left << std::setw(30) << "Tag Name" << ": Value" << std::endl;
        output_file << std::string(50, '-') << std::endl;

        for (int i = 0; i < EXIF_IFD_COUNT; i++)
        {
            ExifContent *content = exif_data->ifd[i];
            if (content)
            {
                for (unsigned int j = 0; j < content->count; j++)
                {
                    print_tag(content->entries[j], output_file);
                }
            }
        }
    }

    output_file.close();
    exif_data_unref(exif_data);
}

int main()
{
    std::string file_name;
    std::string file_type;

    std::cout << "Enter the path to the image file: ";
    std::getline(std::cin, file_name);

    if (file_name.empty())
    {
        std::cerr << "No file path provided. Exiting." << std::endl;
        return 1;
    }

    std::cout << "Enter the output file type (bin, txt, html): ";
    std::getline(std::cin, file_type);

    if (file_type != "bin" && file_type != "txt" && file_type != "html")
    {
        std::cerr << "Invalid file type. Exiting." << std::endl;
        return 1;
    }

    read_exif_data(file_name.c_str(), file_type);

    return 0;
}
