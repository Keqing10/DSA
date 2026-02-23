import os
import subprocess

def format_files():
    # 需要格式化的目录
    directories = ['include', 'test']
    # 需要处理的文件后缀
    extensions = ('.cpp', '.hpp', '.h', '.c', '.cc', '.cxx')
    
    count = 0
    for directory in directories:
        if not os.path.exists(directory):
            print(f"跳过不存在的目录: {directory}")
            continue
            
        print(f"正在处理目录: {directory}")
        for root, dirs, files in os.walk(directory):
            for file in files:
                if file.endswith(extensions):
                    file_path = os.path.join(root, file)
                    try:
                        # 执行 clang-format 命令
                        subprocess.run(['clang-format', '-i', file_path], check=True)
                        print(f"已格式化: {file_path}")
                        count += 1
                    except subprocess.CalledProcessError as e:
                        print(f"格式化失败: {file_path}, 错误: {e}")
                    except FileNotFoundError:
                        print("错误: 未找到 clang-format 命令，请确保已安装并添加到环境变量中。")
                        return

    print(f"\n任务完成！共格式化 {count} 个文件。")

if __name__ == "__main__":
    format_files()
