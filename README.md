# WavAgent

wav ファイルを読み込むライブラリ。OpenAL での使用を見越して、wav ファイルからサンプリング周波数等のメタデータと、波形データを読み込む。左右のチャンネルにも対応する。

## クラス図(概要)

![class diagram](design/WavAgentClassDiagram.png)

## 使用例

wav ファイルを読み込みたいアプリケーションは、まず `WavAgent` オブジェクトを作成する。

```C++
auto wavAgent = WavAgent();
```

その後、読み込みたい wav ファイルのパスを与え、 `Load` 関数を呼び出す。

```C++
wavAgent.Load("data/sound.wav");
```

読み込みが完了したら、サウンドデータを取り出す。 `GetSoundData` に、 `SoundData` のポインタのポインタを渡す。そうすると、渡したポインタが `WavAgent` が保持する `SoundData` を指すようになる。

```C++
SoundData *pSounData = NULL;
wavAgent.GetSoundData(&pSoundData);
```

`SoundData` は波形データとメタデータを持つ。波形データは、各チャンネルごとに、 `signed short` の `vector` となっている。値の範囲は-32768 - 32767 を取る。元の波形データが、符号なし 8bit だったとしても、-32768 - 32767 の範囲にマッピングされる。

`SoundData` に含まれるあるチャンネルの波形を取得するためには、 `GetWave` 関数を使用する。チャンネルは 0-indexed に指定する。なので、チャンネル 1 の波形を取得するためには、0 番の波形データを取得する。

```C++
std::vector<signed char> *pWave;
wavAgent.GetWave(&pWave, 0);
```

サウンドのチャンネル数やサンプリング周波数などのメタデータを取得する場合は、 `SoundData` が保持する `MetaData` を参照する。 `WavAgent` から `SoundData` を取得した時と同様に `MetaData` のポインタのポインタを `SoundData` の `GetMetaData` に渡すと、そのポインタが `SoundData` が保持する `MetaData` を指すようになる。

```C++
MetaData *pMetaData = NULL;
wavAgent.GetMetaData(&pMetaData);
```
