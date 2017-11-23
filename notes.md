#Raytracing

Algoritmo para generar imágenes super realistas con la contra de que el costo de ejecución mucho más grande.

Imágen generada pixel a pixel, "tiramos rayos por cada pixel"

##Representación de recta 

Un punto y un vector

P = 0 + λD

##Representación de Esfera

En base al centro y el radio calculo si el punto P pertence a la esfera o no.

|P - C| = r

##Intersección de rectas y esferas
<TODO> Copiar del cuaderno

##Algoritmo de intercepción de rectas y esferas


# Representa una intersección entre una esfera y una recta
struct inter {
	esfera *e;
	float lambda; #El más cercano a la cámara, siempre es el lambda más chico
}

struct esfera{
	Material m; #Contiene todas las propiedades del material de la esfera
	Vec3 centro;
	float r;
}

INTER intersectar(Vec3 0, D, float λ_min, λ_max){
	INTER i;
	i.e = NULL;
	i.lambda = INF;

	foreach e in esferas {
		# Debo chequear que los lambda recibidos estén dentro de las restricciones de la escena. 
		(λ1, λ2) = intersectar_esfera(e,0,D)
		# La tercer condición toma en cuenta los casos que la recta intersecte más de una esfera. En ese caso, debemos asegurarnos que nos quedamos con el menor λ (el más cercano a la cámara)
		if (λ1 > λ_min && λ1 < λ_max && λ1 < i.λ){
			i.e = e;
			i.λ = λ1
		}
		#Necesito un if análogo al de arriba para λ2
	}
	return i;
}

## Trazar rayo

# Me pasan un rayo y devuelve el color del píxel
Color trazar_rayo(Vec3 O,D, float λ_min, λ_max, int lim_rec) {
	Color res = (0, 0, 0) #Inicializo como negro
	INTER i = intersectar(O, D, λ_min, λ_max)

	if (i.e != NULL){
		Vec3 P = O + i.λD
		#La normal en una esfera se calcula restando P y C
		Vec3 N = P - i.e->centro; 
		Vec3 V = -D;

		res = i.e->m.Cd*IA;

		foreach luz in luces{
			#Resolvemos lambert por cada luz y sumamos la luz
			Vec3 L = luz.pos - P;

			#Como calculamos las intercepciones con esferas matemáticamente perfectas, puede ser posible que el punto interceptado esté dentro de la esfera (por temas de calculos computacionales). Por eso, tenemos una constante E que se asegura que el Punto P se mueva un poquito hacia afuera de la esfera, para no intersectar con la misma esfera al buscar oculusiones.
			inter sombra = intersectar(P, L, E, 1);
			if (sombra.e == NULL ){
				res += lambert(P, N, L, V, i.e->m);

				if(lim_rec > 0 && i.e->m.coef_refl>0){
					Vec3 RR = 2*N*<N,N>-V;
					# A partir de este rayo, calculo el color y lo compongo con el color que ya tenía
					Color cr = trazar_rayo(P, RR, E, INF, lim_rec-1)

					#Mediante combinación lineal con respecto al coeficiente de reflección de la esfera interceptada.
					res = res*(1-i.e->m.coef_refl)+cr*(i.e->m.coef_refl);
				}
				return res;
			}
			
		}
	}
}

## Main

int main(camara){
	Vec3 O = camara;
	for (x=-cw/2, x<cw/2; x++){
		for (y=-ch/2; y<ch/2; y++){
			x' = x * vw/cw;
			y' = y * vh/ch;
			z' = d;

			Vec3 D = (x', y', z');
			Color c = trazar_rayo(O, D, 1, INF);
			put_pixel(x, y, c);
		}
	}
}

## Cálculo de rayo reflejado

Algorítmo recursivo, ya que el comportamiendo de la luz al reflejar es el mismo. Por esto nos conviene, así podemos reutilizar la lógica en trazar_rayo