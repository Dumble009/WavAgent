# WavAgent

wav ファイルを読み込むライブラリ。OpenAL での使用を見越して、wav ファイルからサンプリング周波数等のメタデータと、波形データを読み込む。左右のチャンネルにも対応する。

## クラス図(概要)

![class diagram](design/WavAgentClassDiagram.png)

## 使用例

wav ファイルを読み込みたいアプリケーションは、まず `WavAgent` オブジェクトを作成する。

```C++
auto wavAgent = WavAgent();
```

その後、読み込みたい wav ファイルのパスと、データを設定してほしい `SoundData` のポインタを与え、 `Load` 関数を呼び出す。

```C++
SoundData soundData = SoundData();
wavAgent.Load("data/sound.wav", &soundData);
```

`SoundData` は波形データとメタデータを持つ。波形データは、各チャンネルごとに、 `int` の `vector` となっている。元の波形データの 1 サンプルが 32bit だった場合は、1 要素で 1 サンプルを表現する。元の波形データが、16bit だった場合は、1 要素で 2 つのサンプルを表現する。元の波形データが 8bit だった場合は、1 要素で 2 つのサンプルを表現する。 `int` 型の 32bit の余っている部分に入る値は不定。例えば 1 サンプルが 8bit で、サンプル数を 4 で割った時の余りが 3 の時、残りの 8bit が 0 で埋まっているとは限らない。ユーザに対してはこの実装は隠蔽される。

`SoundData` に含まれる、あるチャンネルの波形を取得するためには、 `GetWave` 関数を使用する。チャンネルは 0-indexed に指定する。なので、チャンネル 1 の波形を取得するためには、0 番の波形データを取得する。波形データは要求する形式の配列先頭のポインタとして渡される。以下の例であれば、符号付き 16bit の波形データのチャンネル 1 を要求している。

```C++
SampleSigned16bit *pWave;
wavAgent.GetWave(&pWave, 0);
```

サウンドのチャンネル数やサンプリング周波数などのメタデータを取得する場合は、 `SoundData` が保持する `MetaData` を参照する。 `WavAgent` から `SoundData` を取得した時と同様に `MetaData` のポインタのポインタを `SoundData` の `GetMetaData` に渡すと、そのポインタが `SoundData` が保持する `MetaData` を指すようになる。

```C++
MetaData *pMetaData = NULL;
soundData.GetMetaData(&pMetaData);
```

なお、全ての関数操作は、返り値として `WavAgentErrorCode` の値を返す。返り値が `WAV_AGENT_SUCCESS` であれば正常終了しており、それ以外であれば、何らかのエラーが発生している。エラーの種類は `WavAgentErrorCode` の値を調べれば分かる。

```C++
WavAgentErrorCode ret = wavAgent.Load("data/sound.wav", &soundData);
if(ret != WavAgentErrorCode::WAV_AGENT_SUCCESS)
{
    std::cerr << "error!" << std::endl;
}
```

`WavAgentErrorCode` は `<<` 演算子をオーバーロードしているので、`cout` 等に出力することが出来る。

```C++
std::cout << WavAgentErrorCode::WAV_AGENT_SUCCESS << std::endl;
// WAV_AGENT_SUCCESSと出力される
```

エラーの詳細な原因調べるためには `ConvertWavAgentErrorCodeToDescription` 関数を使用する。

```C++
std::cout <<
ConvertWavAgentErrorCodeToDescription(WavAgentErrorCode::WAV_AGENT_SUCCESS)
 << std::endl;
// WavAgent : Operation successfully completed. と出力される。
```
