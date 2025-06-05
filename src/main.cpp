#include <camera/camera.h>
#include <color/color.h>
#include <hittable/hittable_list.h>
#include <material/material.h>
#include <hittable/sphere.h>
#include <vec/vec3.h>
#include <math/constants.h>
#include <math/math_utils.h>

int main() {
	hit::HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Colord(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3d(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = math_utils::random<double>();
            Point3d center(a + 0.9 * math_utils::random<double>(), 0.2, b + 0.9 * math_utils::random<double>());

            if ((center - Point3d(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = math_utils::random<double>(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3d(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colord(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3d(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colord(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3d(4, 1, 0), 1.0, material3));

	camera::Camera camera(16.0 / 9.0, 1080, Point3d(13, 2, 3), Point3d(0, 0, 0), Vec3d(0, 1, 0), 20, 0.6, 10.0, 500, 50);
	camera.render(world);

}