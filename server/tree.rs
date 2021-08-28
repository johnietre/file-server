use std::cell::RefCell;
use std::rc::Rc;

struct DirEntry {
    name: String,
    parent: Rc<RefCell<DirEntry>>,
    children: Vec<Rc<RefCell<DirEntry>>>,
    is_dir: bool,
    last_mod: i64,
}

struct FileTree {
    root: Rc<RefCell<DirEntry>>,
    root_path: String,
}

impl FileTree {
    fn new(root_path: &str) -> Self {
        //
    }
}
