use std::{fs, env};
use regex::Regex;

struct Point {
    x: f64,
    y: f64
}

struct Line {
    points: (Point, Point)
}

struct Circle {
    radius: f64,
}

pub trait Segment {
    fn len(&self) -> f64;
}

impl Point {
    fn new( x: f64, y: f64) -> Self {
        Point { x, y }
    }
}

impl Circle {
    fn new(radius: f64) -> Self {
        Circle { radius }
    }
}

impl Line {
    fn new(x0: f64, y0: f64, x1: f64, y1: f64) -> Self {
        Line { points: (Point::new(x0, y0), Point::new(x1, y1)) }
    }
}

impl Segment for Circle {
    fn len(&self) -> f64 {
        2.0 * std::f64::consts::PI * self.radius
    }
}

impl Segment for Line {
    fn len(&self) -> f64 {
        (self.points.0.x - self.points.1.x).abs().sqrt() + (self.points.0.y - self.points.1.y).abs().sqrt()
    }
}

fn main() {

    if env::args().nth(1).is_none() {
        panic!("Please, specify source file");
    }
    let file = env::args().nth(1).unwrap();
    let file_metadata = fs::metadata(&file);
    assert!(file_metadata.unwrap().is_file());
    let source = fs::read_to_string(file).unwrap();
    if source.is_empty() {
        panic!("Source file cannot be empty")
    }

    let float_regex = Regex::new(r"[+-]?([0-9]*[.])?[0-9]+").unwrap();
    let line_regex = Regex::new(r"^Line:\s[+-]?([0-9]*[.])?[0-9]+;[+-]?([0-9]*[.])?[0-9]+;[+-]?([0-9]*[.])?[0-9]+;[+-]?([0-9]*[.])?[0-9]+$").unwrap();
    let circle_regex = Regex::new(r"^Circle:\s[+-]?([0-9]*[.])?[0-9]+;[+-]?([0-9]*[.])?[0-9]+;[+-]?([0-9]*[.])?[0-9]+$").unwrap();

    let mut segments: Vec<Box<dyn Segment>> = Vec::new();
    let mut buff: Vec<f64> = Vec::new();

    for line in source.lines() {
        if line_regex.is_match(line) {
            for cap in float_regex.captures_iter(line) {
                buff.push(cap[0].parse::<f64>().unwrap())
            }
            segments.push(Box::new(Line::new(buff[0],buff[1],buff[2],buff[3])) as Box<dyn Segment>)

        } else if circle_regex.is_match(line) {
            for cap in float_regex.captures_iter(line) {
                buff.push(cap[0].parse::<f64>().unwrap())
            }
            segments.push(Box::new(Circle::new(buff[2])) as Box<dyn Segment>)
        } else {}
        buff.clear();
    }

    segments.sort_by(|a, b| a.len().partial_cmp(&b.len()).unwrap()); // migth panic if a or b containt NaN

    for segment in segments {
        println!("{}", segment.len());
    }
}
