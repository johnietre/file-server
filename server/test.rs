use std::ffi::OsStr;
use std::path;

fn main() {
    let p = path::Path::new("/Programming/github.com/johnietre");
    let mut pbuf = p.to_path_buf();
    let other = Some(OsStr::new("no path"));
    println!("{:?}", pbuf.as_path().file_name().or(other).unwrap());
    pbuf.pop();
    println!("{:?}", pbuf.as_path().file_name().or(other).unwrap());
    pbuf.pop();
    println!("{:?}", pbuf.as_path().file_name().or(other).unwrap());
    pbuf.pop();
    println!("Final: {}", pbuf.as_path().display());
    println!("{:?}", pbuf.as_path().file_name().or(other).unwrap());
}
