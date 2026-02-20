#include <iostream>
#include <fstream>
#include <cstdint> // for uint8_t
#include <vector>

int test_ppm_output_main() {
    const int image_width = 256;
    const int image_height = 256;
    const int max_color_value = 255;

    // Create a vector to store the raw pixel data (3 bytes per pixel: R, G, B)
    std::vector<uint8_t> pixels(image_width * image_height * 3);

    // Generate image data (a gradient from top-left to bottom-right)
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            // Calculate color values (normalized from 0.0 to 1.0)
            double r = (double)i / (image_width - 1);
            double g = (double)j / (image_height - 1);
            double b = 0.25;

            // Convert to integer color values (0 to 255)
            uint8_t ir = static_cast<uint8_t>(255.999 * r);
            uint8_t ig = static_cast<uint8_t>(255.999 * g);
            uint8_t ib = static_cast<uint8_t>(255.999 * b);

            // Store in the pixel array
            int index = (j * image_width + i) * 3;
            pixels[index] = ir;
            pixels[index + 1] = ig;
            pixels[index + 2] = ib;
        }
    }

    // Open the file in binary mode
    std::ofstream ofs("output.ppm", std::ios::out | std::ios::binary);
    if (!ofs) {
        std::cerr << "Can't open file: output.ppm" << std::endl;
        return 1;
    }

    // Write the PPM header
    // P6 magic identifier, width, height, max color value
    ofs << "P6\n" << image_width << " " << image_height << "\n" << max_color_value << "\n";

    // Write the raw pixel data
    ofs.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(uint8_t));

    if (ofs.fail()) {
        std::cerr << "Error writing image data to file" << std::endl;
        return 1;
    }

    ofs.close();

    std::cout << "Successfully created output.ppm (" << image_width << "x" << image_height << ")" << std::endl;

    return 0;
}
