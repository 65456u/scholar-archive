from setuptools import setup, find_packages

setup(
    name="chatflow",
    version="0.1.0",
    description="ChatFlow: A DSL developed specifically for online customer service chatbots.",
    author="Yang Hongchen",
    author_email="yanghongchen@bupt.edu.cn",
    packages=find_packages(),
    install_requires=["lark", "inputimeout", "aioconsole"],
)
