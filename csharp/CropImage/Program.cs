// dotnet add package SixLabors.ImageSharp --version 1.0.0-beta0003
// dotnet build --configuration Release
// dotnet publish --runtime win7-x64
// dotnet build --configuration Release -r win7-x64
// dotnet.exe publish -c Release -r win-x64 -f netcoreapp2.0
// dotnet publish -c release --self-contained --runtime win-x64 --framework netcoreapp2.0

using System;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;
using SixLabors.ImageSharp.Processing;
using SixLabors.ImageSharp.Processing.Transforms;
using SixLabors.Primitives;
using System.IO;
using SixLabors.ImageSharp.Formats.Jpeg;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace CropImage
{
    class Program
    {

        const double PAPER = 76.2;
        const double PAPER_24_INCH = 60.9;//60.96;
        static void Main(string[] args)
        {
            // float cf = Path.GetFileNameWithoutExtension(Environment.GetCommandLineArgs()[0]).ConvertToFloat();
            // Console.WriteLine($"目标宽度为{cf}厘米");
            // if (cf == -1)
            // {
            //     Console.ReadKey();
            //     return;
            // }
            var actions = new List<Action>();
            args = @"C:\Users\Administrator\Desktop\符欢  699 姚佩琪 8寸杂志册".GetJpgFiles().ToArray();

            foreach (var item in args)
            {
                ProcessImage(item);
            }
            // foreach (var item in args)
            // {
            //     if (File.Exists(item))
            //     {
            //         actions.Add(() =>
            //                            {
            //                                CropImageByWidth(item, cf);
            //                            });
            //     }

            // }
            // Parallel.Invoke(new ParallelOptions
            // {
            //     MaxDegreeOfParallelism = 3
            // }, actions.ToArray());
            // Console.ReadKey();
        }
        public static double PX2CM(int px, double resolution)
        {
            return px / resolution * 2.539999918;
        }
        public static double CM2PX(double cm, double resolution)
        {
            return cm / 2.539999918 * resolution;
        }
        private static void CropImageByWidth(string fileName, float targetWidthCentimeter)
        {
            using (var image = Image.Load(fileName))
            {
                int targetWidth = (int)Math.Ceiling(targetWidthCentimeter / 2.54 * image.MetaData.HorizontalResolution);

                if (targetWidth >= image.Bounds().Width)
                {
                    Console.WriteLine($"图片尺寸比目标尺寸小，无需裁剪，跳过:{fileName}");
                    return;
                }


                using (Image<Rgba32> dst = image.Clone(ctx => ctx.Resize(new ResizeOptions
                {
                    Size = new Size(targetWidth, image.Bounds().Height),
                    Mode = ResizeMode.Crop
                })))
                {
                    using (var outStream = new FileStream(fileName, FileMode.OpenOrCreate))
                    {
                        dst.SaveAsJpeg(outStream, new JpegEncoder
                        {
                            Quality = 95
                        });
                        Console.WriteLine($"{fileName} => 分辨率：{image.MetaData.VerticalResolution} 宽：{image.Bounds().Width} 裁剪到 {targetWidth}");

                    }
                }
            }
        }

        private static void ProcessImage(string fileName)
        {
            using (Image<Rgba32> img = Image.Load(fileName))
            {
                var dpi = img.MetaData.HorizontalResolution;
                Console.WriteLine($"[INFO]: dpi => {img.MetaData.VerticalResolution}");
                var wInCentimeter = Math.Round(PX2CM(img.Bounds().Width, dpi), 2);
                var hInCentimeter = Math.Round(PX2CM(img.Bounds().Height, dpi), 2);

                var wRemainder = PAPER_24_INCH % wInCentimeter;
                var hRemainder = PAPER_24_INCH % hInCentimeter;

Console.WriteLine($"{wRemainder} {hRemainder} {wInCentimeter} {hInCentimeter}" );
                // if (wRemainder % 1 > hRemainder % 1)
                // {
                //     var descreaeInCentimeter = Math.Round((PAPER_24_INCH / Math.Round(wRemainder) - wInCentimeter), 2);
                //     if (descreaeInCentimeter < 1)
                //     {
                //        var size=new Size(img.Bounds().Width - Math.Abs((int)CM2PX(descreaeInCentimeter, dpi)), img.Bounds().Height);

                //         Console.WriteLine($"wRemainder % 1：{size}");
                //        CropImage(img, size, fileName);
                //     }
                // }

            }
        }

        private static void CropImage(Image<Rgba32> image, Size size, string outFileName, int quality = 95)
        {
            using (Image<Rgba32> dst = image.Clone(ctx => ctx.Resize(new ResizeOptions
            {
                Size = size,
                Mode = ResizeMode.Crop
            })))
            {
                using (var outStream = new FileStream(outFileName, FileMode.OpenOrCreate))
                {
                    dst.SaveAsJpeg(outStream, new JpegEncoder
                    {
                        Quality = 95
                    });

                }
            }
        }

    }


    static class StringExtensions
    {

        public static float ConvertToFloat(this String s)
        {
            var f = Regex.Match(s, "[0-9\\.]+").Value;
            if (string.IsNullOrWhiteSpace(f)) return -1f;
            return float.Parse(f);
        }
    }

    static class FileExtensions
    {

        public static IEnumerable<string> GetJpgFiles(this string p)
        {
            return Directory.GetFiles(p).Where(i => Regex.IsMatch(i, "\\.(?:jpg|jpeg)$", RegexOptions.IgnoreCase));
        }
    }
}
