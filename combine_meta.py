import pandas as pd

authors = {
    'name': [
        '机器之心',
        '机器之能',
        'ScienceAI'
    ],
    'path': [
        '294c393b-25f7-45b0-bec6-33e3bd344e61.pkl',
        'f2e8c882-a163-443d-8b0c-e9f08ce5d6cb.pkl',
        '0db0310e-6f96-46bc-9151-a50b36421a76.pkl'
    ]
}


def main():
    all_df = pd.DataFrame()
    for name, path in zip(authors['name'], authors['path']):
        df = pd.read_pickle(path)
        # 创建author列，把df的author列全部设为name
        df['author'] = name
        df['author_id'] = path.split('.')[0]
        all_df = pd.concat([all_df, df])
    df = all_df.sort_values(by = 'link')
    df.to_pickle('all.pkl')


if __name__ == '__main__':
    main()
