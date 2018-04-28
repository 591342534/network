#ifndef __MYSORT_H__
#define __MYSORT_H__

namespace MySort
{
#define OPEN_PRINT true

	template<typename T>
	inline void swap( T arr[], int i, int j)
	{
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	template<typename T>
	inline void print( T arr[], int len)
	{
		if ( OPEN_PRINT == false )
			return;

		for ( int i = 0; i < len; ++i)
		{
			std::cout<< arr[i] << "  ";
		}
		std::cout<<std::endl;
	}

	/** 
	 * ֱ�Ӳ�������: 
	 * ÿ�δ�������ȡһ����û��ȡ���������������մ�С��ϵ���뵽�Ѿ�ȡ��������ʹ���Ѿ�ȡ��������Ȼ����
	 */
	template<typename T>
	void insertSort( T * arr, T  len)
	{
		T temp;
		int pos;

		for ( int i = 1; i < len; ++i)
		{
			temp = arr[i];
			pos = i - 1;
			while( pos >= 0 && temp < arr[pos] )
			{
				arr[pos + 1] = arr[pos];
				--pos;
			}
			print(arr, len);
			arr[pos+1] = temp;
		}
	}

	/** 
	 *	ϣ������: 
	 *	shell�������˼·�ǣ���ȡһ��С��n������d1��Ϊ��һ�����������ļ���ȫ����¼�ֳ�d1���顣���о���Ϊdl�ı����ļ�¼����ͬһ�����С�
	 *	���ڸ����ڽ���ֱ�Ӳ�������Ȼ��ȡ�ڶ�������d2<d1�ظ������ķ��������ֱ����ȡ������dt=1(dt<dt-l<��<d2<d1)�������м�¼����ͬһ���н���ֱ�Ӳ�������Ϊֹ��
	 */
	template<typename T>
	void shellSort( T arr[], int  len )
	{
		T temp;
		int pos;
		int d = len; //len >> 1

		do 
		{
			d = d/3 + 1;
			for ( int i = d; i < len; ++i )
			{
				temp = arr[i];
				pos = i - d;

				while ( pos >= 0 && temp < arr[pos] )
				{
					arr[pos + d] = arr[pos];
					pos -= d;
				}

				arr[pos + d] = temp;
			}
		} while ( d > 1);

		/*
		while( d>= 1 )
		{
			for ( int i = d; i < len; ++i )
			{
				temp = arr[i];
				pos = i - d;
				while ( pos >= 0 && temp < arr[pos] )
				{
					arr[pos + d] = arr[pos];
					pos -= d;
				}

				arr[pos + d] = temp;
			}
			print(arr, len);
			d >>= 1;
		}*/
	}

	/**
	 * ѡ������:
	 * ÿ�δ��������ҳ�һ����С�����ŵ���ǰ�������ٴ�ʣ�µ�n-1������ѡ��һ����С�ģ���������ȥ��
	 */
	template<typename T>
	void selectSort( T arr[], int  len )
	{
		T temp;
		int pos, j;

		for ( int i = 0; i < len; ++i )
		{
			temp = arr[i];
			pos = i;

			for ( j = i + 1; j < len; ++j )
			{
				if ( temp > arr[j] )
				{
					temp = arr[j];
					pos = j;
				}
			}

			if ( pos != i )
			{
				arr[pos] = arr[i];
				arr[i] = temp;
			}
			print(arr, len);
		}
	}

	/** �Ѳ������� **/
	template<typename T>
	void heapSort( T arr[], int  len )
	{
		int n = (len - 1) / 2;
		for ( int i = n; i >= 0; --i )
		{
			heapAdjust(arr, i, len);
		}

		print(arr, len);

		for ( int i = len - 1; i >= 0; --i )
		{
			swap(arr, i, 0);
			heapAdjust(arr, 0, i);
			print(arr, i);
		}

		print(arr, len);
	}

	template<typename T>
	static void heapAdjust( T arr[], int pos, int  len )
	{
		T temp = arr[pos];
		int child = pos * 2 + 1;

		while( child < len )
		{
			if ( child + 1 < len && arr[child] < arr[child + 1] )
				++child;

			if ( temp < arr[child] )
			{
				arr[pos] = arr[child];
				pos = child;
				child = pos * 2 + 1;
			}
			else
				break;
		}

		arr[pos] = temp;
	}


	/** ð������ **/
	template<typename T>
	void bubbleSort( T arr[], int  len )
	{
		T temp;
		bool flag = false;
		for ( int i = 0; i < len; ++i )
		{
			for (int j = len - 1; j >= i; --j )
			{
				if ( arr[j] < arr[j-1])
				{
					swap(arr, j, j-1);
					flag = true;
				}
			}
			print(arr, len);

			if ( !flag ) return;
		}
	}

	/** �������� 1 **/
	template<typename T>
	void quickSort( T arr[], int len )
	{
		quickSplit(arr, 0, len-1 );
	}

	template<typename T>
	void quickSplit(T arr[], int left, int right )
	{
		if ( left >= right )
			return;

		T temp = arr[left];

		int i = left;
		int j = right;

		while ( i < j )
		{
			while( i < j && arr[j] >= temp )
				--j;
			while( i < j && arr[i] <= temp )
				++i;

			if ( i < j )
				swap(arr, i, j);
		}

		if ( left != i )
		{
			arr[left] = arr[i];
			arr[i] = temp;
		}

		quickSplit(arr, left, i - 1);
		quickSplit(arr, i + 1, right );
		
	}
	/** �������� 2 **/
	template<typename T>
	void quickSort2( T arr[], int len )
	{
		quickSplit(arr, 0, len-1 );
	}

	template<typename T>
	void quickSplit2(T arr[], int left, int right )
	{
		T middle = arr[ (right + left) / 2 ];

		int i = left;
		int j = right;

		while( i < j )
		{
			while( i < right && arr[i] < middle )
				i++;

			while( j > left && arr[j] > middle )
				j--;

			if ( i <= j )
			{
				if ( i != j )
					swap(arr, i, j);
				i++;
				j--;
			}
		}

		if ( left < j )
			quickSplit( arr, left, j);
		if ( i < right )
			quickSplit(arr, i, right);

		print(arr,10);
	}


}



#endif// __MYSORT_H__
