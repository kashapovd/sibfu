import os
import json
from PIL import Image
import argparse

# Resize given image with PIL
def resizeImageWithPIL(image):
    img = Image.open(image)
    img.thumbnail((200, 200))
    newFileName = image.replace('.', '_thumb.')
    img.save(newFileName)
    return newFileName

# function listing all image files in path and generating report
def generateGalleries(path):
    # Get all files in path
    files = os.listdir(path)
    # Create a list of all images
    images = []
    for file in files:
        if file.endswith(('.jpeg', '.jpg', '.png')) and not "_thumb" in file:
            images.append(path + '/' + file)
    # Create a json report
    report = {
        "gallery": path.split('/')[-1],
        "images": []
    }
    for image in images:
        report["images"].append({
            "name": image.split('/')[-1],
            "file": image,
            "thumb": resizeImageWithPIL(image)
        })
    # Save json report
    reportPath = path + '/' + path.split('/')[-1] + '.json'
    with open(reportPath, 'w') as outfile:
        json.dump(report, outfile, indent=4)

# function listing all json files in subfolders and generating report
def generateGalleriesFromJson(path):
    # Get all subfolders in path
    folders = os.listdir(path)
    # Create a list of all json files
    jsonFiles = []
    for folder in folders:
        if os.path.isdir(path + '/' + folder):
            files = os.listdir(path + '/' + folder)
            for file in files:
                if file.endswith('.json'):
                    jsonFiles.append(path + '/' + folder + '/' + file)
    # Create a list of all galleries
    galleries = []
    for jsonFile in jsonFiles:
        with open(jsonFile) as data_file:
            data = json.load(data_file)
        galleries.append(data["gallery"])
    # Create a json report
    report = {
        "galleries": []
    }
    for gallery in galleries:
        report["galleries"].append({
            "name": gallery,
            "path": path.replace("\\", "/").split("/")[-1] + '/' + gallery
        })
    # Save json report
    reportPath = path + '/' + 'galleries.json'
    with open(reportPath, 'w') as outfile:
        json.dump(report, outfile, indent=4)

# Python main entrypoint
if __name__ == '__main__':
    # Using argparse create a command line argument for functions with path
    parser = argparse.ArgumentParser(description='Generate galleries.')
    parser.add_argument('-p', '--path', type=str, help='path to the directory')
    parser.add_argument('-g', '--generate', action='store_true', help='Generate galleries.')
    parser.add_argument('-j', '--json', action='store_true', help='Generate galleries from json files.')
    args = parser.parse_args()

    # Call function if certain argparse flag passed else print usage
    if args.generate:
        if not args.path:
            parser.error('Path is required for generate flag.')
        else:
            generateGalleries(args.path)
    elif args.json:
        generateGalleriesFromJson(os.getcwd())
    else:
        parser.print_usage()
