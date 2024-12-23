import os

# 定义目录和文件结构
structure = {
    "src": {
        "index": ["__init__.py", "builder.py", "storage.py", "updater.py", "search.py"],
        "data": ["__init__.py", "loader.py", "preprocessor.py"],
        "api": ["__init__.py", "endpoints.py", "handlers.py"],
        "utils": ["__init__.py", "logger.py", "config.py"],
        "spider": ["__init__.py", "crawler.py", "item.py", "pipelines.py", "settings.py"],
        "app.py": None,
        "config.py": None,
    },
    "tests": ["__init__.py", "test_index.py", "test_data.py", "test_api.py", "test_utils.py"],
    "docs": ["index.md", "api.md", "architecture.md", "usage.md"],
    "scripts": ["setup.sh", "deploy.sh", "backup.sh"],
    ".gitignore": None,
    "requirements.txt": None,
    "README.md": None,
    "LICENSE": None

}


def create_structure(base_path, structure):
    """
    根据结构字典创建目录和文件
    :param base_path: 基础路径
    :param structure: 结构字典
    """
    for name, content in structure.items():
        path = os.path.join(base_path, name)
        if isinstance(content, dict):
            # 创建目录
            os.makedirs(path, exist_ok = True)
            # 递归创建子结构
            create_structure(path, content)
        elif isinstance(content, list):
            # 创建目录
            os.makedirs(path, exist_ok = True)
            for file_name in content:
                # # 创建文件
                # file_path = os.path.join(path, file_name)
                # open(file_path, 'w').close()
                # 判断文件是否存在，若不存在则创建文件
                if not os.path.exists(os.path.join(path, file_name)):
                    open(os.path.join(path, file_name), 'w').close()
        else:
            # 创建文件
            open(path, 'w').close()


if __name__ == "__main__":
    base_path = os.getcwd()
    create_structure(base_path, structure)
    print("目录和文件结构已创建完成。")
