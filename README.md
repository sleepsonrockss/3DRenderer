# 🎨 3D Renderer

A 3D renderer built from scratch in C, implementing the core mathematics
and algorithms behind ray tracing to render three-dimensional scenes
with accurate lighting and shading. No external graphics libraries — just
pure C, vectors, and geometry.

## 🖼️ Sample Output

> *Simulated render — three spheres with point lighting, specular highlights, and ground shadows.*


> To generate your own output, build and run the renderer. The result is written
> as a `.ppm` image file. Convert it to `.png` with:
> ```
> convert output.ppm sample_render.png
> ```

## 🔍 How It Works

The renderer works by casting rays from a virtual camera into a 3D scene
and computing intersections with geometric objects (spheres). For each pixel
on the output image, a ray is traced from the camera through that pixel into
the scene. When a ray hits a surface, the renderer calculates the color at
that point based on the object's material and light sources — simulating how
light actually behaves in the real world.

Key concepts implemented:

- **Ray-sphere intersection** — mathematical detection of where a ray meets a sphere in 3D space
- **Vector arithmetic** — dot products, cross products, normalization, and reflection used throughout the rendering pipeline
- **Color computation** — shading based on surface normals and light direction
- **Camera model** — projecting a 3D scene onto a 2D image plane

## 🛠️ Built With

- C
- Makefile

## 📁 Structure

```
├── assg.c / assg.h       # Core renderer logic and scene setup
├── spheres.c / spheres.h # Sphere geometry and ray intersection
├── vector.c / vector.h   # 3D vector math (dot product, normalization, etc.)
├── color.c / color.h     # Color representation and shading
└── Makefile              # Build configuration
```

## 🚀 Getting Started

1. Clone the repo
2. Build the project:
```
make
```
3. Run the renderer:
```
./renderer
```

> Output is written to a `.ppm` image file, which can be opened with any
> image viewer that supports the format (e.g. GIMP, Preview on macOS).

## 💡 Background

Ray tracing is the foundation of modern photorealistic rendering, used in
film, game engines, and simulation. Building one from scratch in C requires
a solid understanding of linear algebra, 3D geometry, and low-level systems
programming — making this a great exercise in bridging mathematical theory
with efficient implementation.
