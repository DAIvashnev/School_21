package ex00;

import java.util.UUID;

public class Transaction {
    private final UUID id;
    private final User recipient;
    private final User sender;
    private final TransferCategory transfer;
    private final double sum;

    Transaction(User recipient, User sender, TransferCategory transfer, double sum) {
        id = UUID.randomUUID();
        this.recipient = recipient;
        this.sender = sender;
        this.transfer = transfer;
        if (transfer == TransferCategory.DEBITS && sum > 0) {
            this.sum = sum;
        } else if (transfer == TransferCategory.CREDITS && sum < 0) {
            this.sum = sum;
        } else {
            this.sum = 0;
        }
    }

    public UUID getId() {
        return id;
    }

    public User getUserRecipient() {
        return recipient;
    }

    public User getUserSender() {
        return sender;
    }

    public TransferCategory getTransfer() {
        return transfer;
    }

    public double getSum() {
        return sum;
    }

    public String getAllData() {
        return "Transaction: id - " + id + ", UserRecipient - " + recipient + ", UserSender - " + sender + "," +
                " Transfer - " + transfer + ", sum = " + sum + "\n";
    }
}
