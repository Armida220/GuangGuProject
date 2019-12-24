#pragma once
#include "zipfile.h"

UTILITY_NS
	

	/// \brief PNG���ݵ���ɫ����
	enum GsPNGColorType
	{
		eUnknownPNGColorType,
		eGrayScale1,
		eGrayScale2,
		eGrayScale4,
		eGrayScale8,
		eGrayScale16,
		eRGB8,
		eBGR8,
		eRGB16,
		eBGR16,
		ePalette1,
		ePalette2,
		ePalette4,
		ePalette8,
		eAlphaGrayScale8,
		eAlphaGrayScale16,
		eARGB8,
		eRGBA8,
		eABGR8,
		eBGRA8,
		eARGB16,
		eRGBA16,
		eABGR16,
		eBGRA16,
	};

	/// \brief PNG��ɫ��
	struct GS_API  GsPNGPalette
	{
		GsPNGPalette();
		bool		WithAlpha;
		unsigned int Size;
		unsigned int RGBAColor[256];
	};

	/// \brief ����PNG��д
	/// \details https://www.w3.org/TR/PNG
	class GS_API GsPNG:GsZlibStream
	{
	public:
		/// \brief PNG��д�����еĴ���
		enum ErrorCode
		{
			eNoError,
			eGeneralError,
		};
		/*
		   -------------
		   |C | B | D |
		   ------------
		   |A | x |   |
		   ------------

		Type	Name	Filter Function	Reconstruction Function
		0	None	Filt(x) = Orig(x)	Recon(x) = Filt(x)
		1	Sub	Filt(x) = Orig(x) - Orig(a)	Recon(x) = Filt(x) + Recon(a)
		2	Up	Filt(x) = Orig(x) - Orig(b)	Recon(x) = Filt(x) + Recon(b)
		3	Average	Filt(x) = Orig(x) - floor((Orig(a) + Orig(b)) / 2)	Recon(x) = Filt(x) + floor((Recon(a) + Recon(b)) / 2)
		4	Paeth	Filt(x) = Orig(x) - PaethPredictor(Orig(a), Orig(b), Orig(c))	Recon(x) = Filt(x) + PaethPredictor(Recon(a), Recon(b), Recon(c))

		x	the byte being filtered;
		a	the byte corresponding to x in the pixel immediately before the pixel containing x(or the byte immediately before x, when the bit depth is less than 8);
		b	the byte corresponding to x in the previous scanline;
		c	the byte corresponding to b in the pixel immediately before the pixel containing b(or the byte immediately before b, when the bit depth is less than 8).
		*/
		enum FilterTypes
		{
				eFTNone =0,
				eFTSub = 1,
				eFTUp =2,
				eFTAverage = 3,
				eFTPaeth =4,
		};
	private:
		ErrorCode m_Error;
		unsigned int m_CRC;
		GsString m_ErrorMessage;
		int m_Row;
		int m_ReadRGBA8RowCount;
		int m_W, m_H, m_Depth;
		GsGrowByteBuffer m_Cache, m_Cache1, m_CacheBefore, m_Cachel7;
		GsPNGPalette m_Palette;
		GsPNGColorType m_Type;
		int m_ScanCount;
		
		GsVector<unsigned int>  m_vPassW;
		GsVector<unsigned int>  m_vPassH;
		//GsVector<size_t>		m_vFilterPassStart;
		//GsVector<size_t>		m_vPaddedPassStart;
		//GsVector<size_t>		m_vPassStart;

		/*
		IHDR	No	Shall be first
		PLTE	No	Before first IDAT
		IDAT	Yes	Multiple IDAT chunks shall be consecutive
		IEND	No	Shall be last
		cHRM	No	Before PLTE and IDAT
		gAMA	No	Before PLTE and IDAT
		iCCP	No	Before PLTE and IDAT.If the iCCP chunk is present, the sRGB chunk should not be present.
		sBIT	No	Before PLTE and IDAT
		sRGB	No	Before PLTE and IDAT.If the sRGB chunk is present, the iCCP chunk should not be present.
		bKGD	No	After PLTE; before IDAT
		hIST	No	After PLTE; before IDAT
		tRNS	No	After PLTE; before IDAT
		pHYs	No	Before IDAT
		sPLT	Yes	Before IDAT
		tIME	No	None
		iTXt	Yes	None
		tEXt	Yes	None
		zTXt	Yes	None
		*/
		enum ChunkType
		{
			eErrorChunk,
			eIHDR,
			ePLTE,
			eIDAT,
			eIEND,
			
			ecHRM,
			egAMA,
			eiCCP,
			esBIT,
			esRGB,
			ebKGD,
			ehIST,
			etRNS,
			epHYs,
			epPLT,
			etIME,
			eiTXt,
			etEXt,
			ezTXt
		};
		ChunkType ReadChunkHead(unsigned int& crc, unsigned int& length);
		const unsigned char* ReadChunkData(unsigned int crc, unsigned int length, bool &crcOK);

		virtual void Put8(unsigned char a);
		void Put32(unsigned int v);
		void BeginChunk(const char* id, int len);
		void EndChunk(); 
		
		const unsigned char *Read(int& nSize);

		void Error(ErrorCode code);
		void Error(const char* msg);
		void Succeed();

		template<class T>
		T Error(ErrorCode  nCode, T result)
		{
			Error(nCode);
			return result;
		}

		template<class T>
		T Error(const char* msg, T result)
		{
			Error(msg);
			return result;
		}
		template<class T>
		T Succeed(T result)
		{
			Succeed();
			return result;
		}
		
		virtual const unsigned char* OnNextInputBuffer(unsigned int& size);
		virtual void OnWrite(const unsigned char* data, int nLen);
		virtual void OnChunkData(const unsigned char* data, int nSize);

		bool DirectCopyType();
		void CopyRow(const unsigned char* row, unsigned char* cache, int nStride);
		//ÿ��ʹ�ò�ͬ�Ĺ����㷨ѹ������ѹ���ģ�������ʵ��zip��ѹ������أ������ˣ���ԭ����
		void Filtering(FilterTypes etype, unsigned char* row, int length);
	protected:

		/// \brief ���Ǵ˺�����ʵ�ֽ�������PNGʱ��д����
		virtual int OnPNGData(unsigned char* data, int nLen,bool bWrite=true) = 0;
	public:
		/// \brief ȱʡ���죬����PNG
		GsPNG();
		/// \brief ȱʡ���죬����PNG
		GsPNG(int w, int h, GsPNGColorType type = eRGBA8);
		virtual ~GsPNG() {};

		/// \brief ����������
		ErrorCode LastErrorCode();
		/// \brief ��������
		const char* LastErrorMessage();
		/// \brief ������߽��������
		int Row();
		/// \brief ������ɫ���ͺͿ�ȼ���һ�е��ֽڳ���
		static int Stride(GsPNGColorType type, int width);
		/// \brief �ж�8���ֽڳ��ȵ��ļ�ͷ�Ƿ���PNG���ݱ�ǩ
		static bool IsPNGSignature(const unsigned char* head);

		/// \brief �߶�
		int Height();
		/// \brief ���
		int Width();
		/// \brief ���ֽڳ���
		int Stride();
		/// \brief ��ɫ����
		GsPNGColorType  ColorType();
		/// \brief ��ɫ��
		GsPNGPalette& Palette();
		/// \brief ��ʼ����
		/// \details   BeginSave();
		/// \details   for(...){
		/// \details      SaveRow(..);}
		/// \details   FinishSave();
		bool BeginSave();

		/// \brief ����һ��
		void SaveRow(const unsigned char* row);
		/// \brief ��������
		void FinishSave();

		/// \brief ��ʼ����
		/// \details   BeginRead();
		/// \details   while(ReadRow(..){...}
		/// \details   FinishRead();
		bool BeginRead();

		/// \brief ����һ��
		bool ReadRow(unsigned char* row);
		
		/// \brief ����һ��,��RGBA8�ĸ�ʽ���
		bool ReadRGBA8Row(unsigned char* row);

		/// \brief ��������
		void FinishRead();

		/// \brief ��ȡɨ�����
		int ScanCount();
	};

	/// \brief ���ڴ������߱���PNG
	class GS_API  GsMemoryPNG :public GsPNG
	{
		const unsigned char* m_buff;
		int m_Offset,m_nSize;
		GsByteBuffer* m_pBuffer;
		GsGrowByteBuffer  m_Buffer;
	protected:
		/// \brief ��д����
		virtual int OnPNGData(unsigned char* data, int nLen, bool bWrite = true);
	public:
		/// \brief ���ڴ�����
		GsMemoryPNG(const unsigned char* buff,int nSize);
		/// \brief ���ڴ�����
		GsMemoryPNG(GsByteBuffer* buff);
		
		/// \brief ���뵽�ڴ�
		GsMemoryPNG(int w, int h, GsPNGColorType type = eRGBA8);

		/// \brief ���ڴ�����
		GsMemoryPNG(GsByteBuffer* buff,int w,int h, GsPNGColorType type = eRGBA8);
		
		~GsMemoryPNG();

		/// \brief ��ȡ�����õ��ڴ�
		GsByteBuffer* MemoryBuffer();
	};

	/// \brief ���ļ���������PNG
	class GS_API GsFilePNG :public GsPNG
	{
		FILE* m_F;
	protected:

		/// \brief ���ļ���д
		virtual int OnPNGData(unsigned char* data, int nLen, bool bWrite = true);
		 
	public:
		/// \brief ���ļ�����
		GsFilePNG(const char* file);
		/// \brief ���뵽�ļ�
		GsFilePNG(const char* file, int w, int h, GsPNGColorType type = eRGBA8);
		~GsFilePNG();
	};

UTILITY_ENDNS