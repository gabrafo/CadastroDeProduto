import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Program {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Sistema de cadastro de produtos");
        System.out.println("-------------------------------");
        List<Product> products = new ArrayList<>();
        boolean addAnotherProduct = true;
        
        while(addAnotherProduct){
        System.out.print("\nInsira o nome do produto: ");
        String name = sc.nextLine();
        System.out.print("Insira a descrição do produto: ");
        String description = sc.nextLine();
        System.out.print("Insira o preço do produto: R$");
        Double price = sc.nextDouble();
        System.out.print("O produto está disponível no estoque?(S/N) ");
        boolean isAvailable = checkAnswer(sc);
        products.add(new Product(name, description, price, isAvailable));

        Collections.sort(products, (p1, p2) -> Double.compare(p1.getPrice(), p2.getPrice()));
        // OBS: Pensei em criar um método para ordenar usando Shell Sort, Quick Sort ou outro método de ordenação,
        // mas o Java tem uma biblioteca que já faz isso sem a necessidade desse método. Portanto, vou deixar pra
        // comprovar esses conhecimentos na solução em C++.

        System.out.println("\nLista de Produtos:");
        for (Product product : products) {
            System.out.println(product.getName() + " - R$" + product.getPrice());
        }

        System.out.print("Você deseja adicionar um novo produto?(S/N) ");
        addAnotherProduct = checkAnswer(sc);
        }

        sc.close();
    }

    public static boolean checkAnswer(Scanner sc) {
        boolean validAnswer = false;
        while (!validAnswer) {
            try {
                char resp = sc.next().charAt(0);
                sc.nextLine(); // Limpa o buffer do scanner
                if (resp == 's' || resp == 'S') {
                    validAnswer = true;
                    return true;
                } else if (resp == 'n' || resp == 'N') {
                    validAnswer = true;
                    return false;
                } else {
                    System.out.println("Resposta inválida. Digite 'S' para sim ou 'N' para não.");
                }
            } catch (Exception e) {
                System.out.println("Resposta inválida.");
                sc.nextLine();
            }
        }
        return false;
    }
}