public class Product{
    private String name;
    private String description;
    private Double price;
    private boolean isAvailable;

    public Product(){
    }

    public Product(String name, String description, Double price, boolean isAvailable) {
        this.name = name;
        this.description = description;
        this.price = price;
        this.isAvailable = isAvailable;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public boolean getIsAvailable() {
        return isAvailable;
    }

    public void setIsAvailable(boolean isAvailable) {
        this.isAvailable = isAvailable;
    }

    @Override
    public String toString() {
        String disponibilidade;
        if(isAvailable){
            disponibilidade = "Disponível";
        } else {
            disponibilidade = "Indisponível";
        }
        return "Dados do produto:\n"
                + "Nome: " + name 
                + "\nDescrição: " + description
                + "\nPreço: " + price 
                + "\nDisponibilidade: " + disponibilidade;
    }
}