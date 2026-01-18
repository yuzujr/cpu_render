#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "shaders.hpp"

const int w = 1920;
const int h = 1080;
const int frames = 120;
const RenderCtx g_ctx{.w = w, .h = h, .frames = frames};

int main() {
    auto gen_from_to = [&](int from, int to) {
        std::vector<unsigned char> buf;
        buf.reserve(w * h * 3);
        for (int frame = from; frame < to; ++frame) {
            std::string output_path =
                std::format("output/tmp/output-{:03d}.ppm", frame);
            std::fstream f(output_path, std::ios::out | std::ios::binary);
            if (!f) {
                std::cerr << "Failed to open: " << output_path << "\n";
                continue;
            }
            f << "P6\n";
            f << std::format("{} {}\n", w, h);
            f << "255\n";
            buf.clear();
            shader4(g_ctx, frame, buf);
            f.write(reinterpret_cast<const char*>(buf.data()), buf.size());
            f.close();
            std::cout << "Generated " << output_path << '\n';
        }
    };

    std::filesystem::create_directories("output/tmp");

    int tc = (int)std::thread::hardware_concurrency();
    if (tc <= 0) tc = 1;
    tc = std::min(tc, frames);

    std::vector<std::jthread> threads;
    threads.reserve(tc);

    int avg_job = frames / tc;
    int left_job = frames % tc;

    int now = 0;
    for (int t = 0; t < tc; ++t) {
        int actual_job = avg_job + (left_job > 0 ? 1 : 0);
        if (left_job > 0) {
            --left_job;
        }

        threads.emplace_back(gen_from_to, now, now + actual_job);
        now += actual_job;
    }

    return 0;
}
