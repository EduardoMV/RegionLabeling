# Image Region Labeling and Centroid Detection

This C++ program takes an input image, performs binary thresholding, labels connected regions, and detects the centroids of these labeled regions. The labeled regions are saved as an image, and centroids are marked with white circles.

## Getting Started

### Prerequisites

- OpenCV library (3.x or later)

### Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/EduardoMV/RegionLabeling.git
    cd RegionLabeling
    ```

2. **Build the executable:**

    ```bash
    g++ main.cpp -o region_detection `pkg-config --cflags --libs opencv`
    ```

## Usage

Run the executable, providing the path to the input image:

```bash
./region_detection path/to/your/image.png
```

## Result

The program generates two output images:

     - **labeled_regions.jpg:** Image with labeled regions.
     - **centroids.jpg:** Image with labeled regions and marked centroids.
