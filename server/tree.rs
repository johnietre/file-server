use std::fs;
use std::path::Path;
use std::sync::{Arc, RwLock};
use std::time::UNIX_EPOCH;

type SafeDirEntry = Arc<RwLock<DirEntry>>,

pub struct DirEntry {
    name: String,
    parent: Option<SafeDirEntry>,
    children: Vec<SafeDirEntry>,
    is_dir: bool,
    last_mod: i64,
}

pub struct FileTree {
    root: Arc<RwLock<DirEntry>>,
    root_path: String,
}

impl FileTree {
    fn new<P: AsRef<Path>>(root_path: P) -> Self {
        fn build_dir(dir_path: P, dir: &SafeDirEntry) -> Result<()> {
            for entry in dir_path.read_dir()? {
                let entry = entry?;
                let meta = entry.metadata()?;
                let is_dir = meta.is_dir();
                if !meta.is_file() && !is_dir {
                    continue;
                }
                let mut de = Arc::new(RwLock::new(DirEntry {
                    name: entry.into_string().unwrap(),
                    parent: Arc::clone(dir),
                    children: vec![],
                    is_dir: is_dir,
                    last_mod: meta.modified()?
                        .duration_since(UNIX_EPOCH)
                        .unwrap()
                        .as_secs() as i64,
                }));
                if is_dir {
                    build_dir(dir_path.join().as_path(), de)?;
                }
                dir.write().unwrap();
                //
            }
        }
        if !root_path.is_dir() {
            return;
        }
        let root: SafeDirEntry = Arc::new(RwLock::new(DirEntry {
            name: 
        }));
    }
}
