#include <iostream>
using namespace std;
class Simplex
{
    private:
        unsigned int values_count;
        unsigned int limitations_count;
        double **limits_coeficions;
		double *purpose_function_coeficions;
		double *b;
    
    public:
	Simplex ()
	{
		values_count = 0;
		limitations_count = 0;
		limits_coeficions = NULL;
		purpose_function_coeficions = NULL;
		b = NULL;
	}
        Simplex ( unsigned int v , unsigned int l , double *p = NULL, double **lim = NULL, double *bb = NULL )
	{
		values_count = v;
		limitations_count = l;
		limits_coeficions = lim;
		purpose_function_coeficions = p;
		b = bb;
	}

	Simplex ( unsigned int v , unsigned int l )
	{
		values_count = v;
		limitations_count = l;
		b = new double [l];
		limits_coeficions = new double* [l];
		purpose_function_coeficions = new double [v];
		for ( int i = 0 ; i < l ; ++i ) {
			b [i] = 0;
			limits_coeficions [i] = new double [v];
			purpose_function_coeficions [i] = 0;
			for ( int j = 0 ; j < v ; ++j ) {
				limits_coeficions [i][j] = 0;
			}
		}
	}
	


        void set_values_count ( unsigned int v )
        {
            values_count = v;
        }
        
        void set_limitations_count ( unsigned int l )
        {
            limitations_count = l;
        }

        void set_limits_coeficion ( int i , int j , double v )
        {
            limits_coeficions[i][j] = v;
        }

	void set_b( int i , double d )
	{
		b[i] = d;
	}

	void set_purpose_function_coeficion ( int i , double v )
	{
		purpose_function_coeficions [i] = v;
	}
	
	double get_b ( int i )
	{
		return b[i];
	}

	double get_limit_coeficion ( int i , int j )	
	{
		double a = limits_coeficions[i][j] ;
		return a;
	}

	double get_purpose_function_coeficion ( int i )
	{
		return purpose_function_coeficions [i];
	}

	unsigned int get_values_count()
	{
		return values_count;
	}

	unsigned int get_limitation_count()
	{
		return limitations_count;
	}

	
};

int check_last_line ( double **m , unsigned int row , unsigned int col  )
{
	int k = 0;
	for ( int i = 0; i < col ; i++ ){
		if ( m[ row - 1 ][i] < 0 ) {
			k++;
		}
	}

	return k;
}

void simplex_method ( Simplex & s )
{
	unsigned int row = s.get_limitation_count() + 1;
	unsigned int col = s.get_values_count() + row + 1;
	double **m = new double *[row];
	for (int i = 0; i < row ; ++i ) {
		m[i] = new double [col];
	}
	for (int i = 0; i < row ; ++i ) {
		for (int j = 0; j < col ; j++) {
			if ( i < s.get_limitation_count() ) {
				if ( j < s.get_values_count() ) {
					m[i][j] =  s.get_limit_coeficion ( i, j );
					m[ row - 1 ][j] = s.get_purpose_function_coeficion(j) * (-1);
				}

				else {
					m[i][j] = 0;
					m[i][ i + s.get_values_count() ] = 1;
					m[ row -1 ][j] = 0;
				}
				m [i][ col - 1 ] = s.get_b(i);
			}
			m[i][ col - 2 ] = 0;
			m [ row - 1 ][ col - 2 ] = 1;
			m [ row - 1 ][ col - 1 ] = 0;
		}
	}
	while ( check_last_line( m, row, col ) ) {
		double min;
		min = s.get_purpose_function_coeficion(0);
		int c = 0;
		for ( int i = 0 ; i < s.get_values_count() ; i++ ) {
			if ( m[ row - 1 ][i] < min ) {
				min = m[ row - 1 ][i];
				c = i;// min i syuny
			}
		}

		int c1 = 0;
		for ( int i = 0; i < row - 2 ; i++ ) {
			if ( m[i][c] > 0 ) {
				min = m[i][ col - 1 ] / m[i][c];
				if ( min > m[ i + 1 ][ col - 1 ] / m[ i + 1 ][c] ) {
					min = m[ i + 1 ][ col - 1 ] / m[ i + 1 ][c];
					c1 = i + 1 ;//min  i toxy
				}

			}
		}

		double k = m[c1][c];
		for ( int i = 0; i < col; i++ ) {
			m[c1][i] = m[c1][i] / k ;
		}

		for ( int i = 0 ; i < row ; i++ ) {
			if ( i != c1 ) {
				k = m[i][c];
				for ( int j = 0 ; j < col; j++ ) {
					m[i][j] = m[i][j] - m[c1][j] * k;
				}
			}
		}

	}

	for ( int i = 0 ; i < row; i++ ) {
		for ( int j = 0; j < col ; j++ ){
			cout<<m[i][j]<<"       ";
		}
		cout<<endl;
	}
		
}

int main ()
{
	double *f = new double [2];
	double **p = new double* [3];
	double *b = new double [3];
	f[0] = 2;
	f[1] = 3;
	b[0] = 100;
	b[1] = 360;
	b[2] = 120;
	for ( int i = 0; i < 3; i++){
		p[i] = new double [2];
	}
	p[0][0] = 1;
	p[0][1] = 1;
	p[1][0] = 6;
	p[1][1] = 3;
	p[2][0] = 1;
	p[2][1] = 2;
	Simplex a ( 2, 3, f, p, b);
	simplex_method ( a );
	//cout<<check_last_line(p,3)<<endl;
	return 0;
}
