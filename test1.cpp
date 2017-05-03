#include <gtest/gtest.h>

#include <string>

extern "C" {
  #include <jpeglib.h>
  #include <jpeglib.h>
  #include <jerror.h>
}

TEST(libjpeg, load) {
  auto path = std::string("image.jpg");
  const char* FileName = path.c_str();
  unsigned long x, y;
  unsigned int texture_id;
  unsigned long data_size;     // length of the file
  int channels;               //  3 =>RGB   4 =>RGBA
  unsigned int type;
  unsigned char * rowptr[1];    // pointer to an array
  unsigned char * jdata;        // data for the image
  struct jpeg_decompress_struct info; //for our jpeg info
  struct jpeg_error_mgr err;          //the error handler

  FILE* file = fopen(FileName, "rb");

  info.err = jpeg_std_error(& err);
  jpeg_create_decompress(& info);

  ASSERT_TRUE(file && "Error reading JPEG file!");

  jpeg_stdio_src(&info, file);
  jpeg_read_header(&info, TRUE);

  jpeg_start_decompress(&info);

  x = info.output_width;
  y = info.output_height;
  channels = info.num_components;
  // type = GL_RGB;

  // if (channels == 4) {
    // type = GL_RGBA;
  // }

  data_size = x * y * 3;

  jdata = (unsigned char *)malloc(data_size);
  while (info.output_scanline < info.output_height) {
    rowptr[0] = (unsigned char *)jdata + 3 * info.output_width * info.output_scanline;
    jpeg_read_scanlines(&info, rowptr, 1);
  }

  jpeg_finish_decompress(&info);
}
