# CPU Render

A CPU-based shader renderer that generates animated sequences and compiles them into videos.

## Usage

### 1. Adding Shaders (Optional)

Create your shader functions in [src/shaders.hpp](src/shaders.hpp) with the following signature:

```cpp
inline void shaderN(const RenderCtx& ctx, int frame,
                    std::vector<unsigned char>& buf) {
    for (int y = 0; y < ctx.h; ++y) {
        for (int x = 0; x < ctx.w; ++x) {
            // Your shader logic here
            
            // Push RGB values (0-255) to buf
            buf.push_back(r);
            buf.push_back(g);
            buf.push_back(b);
        }
    }
}
```

**Function signature requirements:**
- `ctx`: Provides width, height, and total frames
- `frame`: Current frame number for time calculation
- `buf`: Output buffer to fill with RGB pixels (must contain `ctx.w * ctx.h * 3` bytes)

### 2. Configuring Render Parameters (Optional)

Edit [src/main.cpp](src/main.cpp) to adjust:

```cpp
const int w = 1920;        // Width in pixels
const int h = 1080;        // Height in pixels
const int frames = 180;    // Total number of frames
```

Call your shader function in `main()`:

```cpp
shader3(g_ctx, frame, buf);  // Change to your shader
```

### 3. Rendering

Generate frames:
```bash
make run
```

This will:
- Generate frames in parallel using all available CPU cores
- Output PPM images to `output/tmp/`

### 4. Creating Video

Generate video and open it (Linux only):
```bash
make open
```

This will:
- Use `ffmpeg` to compile all frames into an MP4 video
- Save the video to `output/output-TIMESTAMP.mp4`
- Automatically open the video with `mpv`

**Note:** Requires `ffmpeg` and `mpv` to be installed on your system.

Windows users can manually use `ffmpeg` to create the video from the frames.

## Screenshots

### Shader 1
<img width="1920" height="1080" alt="2026-01-17 17-35-47" src="https://github.com/user-attachments/assets/f584faff-961e-425b-a55b-ba8081267ad2" />

### Shader 2
<img width="1920" height="1080" alt="2026-01-17 17-35-58" src="https://github.com/user-attachments/assets/99e14302-609f-4a31-8005-7108eeba43fa" />

### Shader 3
<img width="1920" height="1080" alt="2026-01-17 17-34-51" src="https://github.com/user-attachments/assets/b4c4a4d2-a90b-4ea8-80b6-a85a8c1804a6" />

## Dependencies

- C++20 compatible compiler (g++)
- ffmpeg (for video generation)
- mpv (for video playback)
