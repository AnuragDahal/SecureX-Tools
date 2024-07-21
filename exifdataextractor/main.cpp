#include <iostream>
#include <libexif/exif-data.h>

void print_tag(ExifEntry *entry)
{
    char buf[1024];

    if (entry)
    {
        exif_entry_get_value(entry, buf, sizeof(buf));
        if (*buf)
        {
            std::cout << exif_tag_get_name(entry->tag) << ": " << buf << std::endl;
        }
        else
        {
            std::cout << exif_tag_get_name(entry->tag) << ": <no data>" << std::endl;
        }
    }
}

void read_exif_data(const char *file_name)
{
    ExifData *exif_data = exif_data_new_from_file(file_name);
    if (!exif_data)
    {
        std::cerr << "No EXIF data found in file " << file_name << std::endl;
        return;
    }

    std::cout << "EXIF data for file: " << file_name << std::endl;

    // Iterate over the IFDs (Image File Directories)
    for (int i = 0; i < EXIF_IFD_COUNT; i++)
    {
        ExifContent *content = exif_data->ifd[i];
        if (content)
        {
            for (unsigned int j = 0; j < content->count; j++)
            {
                print_tag(content->entries[j]);
            }
        }
    }

    exif_data_unref(exif_data);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <image_file>" << std::endl;
        return 1;
    }

    read_exif_data(argv[1]);

    return 0;
}