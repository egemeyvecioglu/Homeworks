import java.util.ArrayList;

public class PlaylistNodeSecondaryIndex extends PlaylistNode {
	private ArrayList<String> genres;
	private ArrayList<PlaylistNode> children;

	public PlaylistNodeSecondaryIndex(PlaylistNode parent) {
		super(parent);
		genres = new ArrayList<String>();
		children = new ArrayList<PlaylistNode>();
		this.type = PlaylistNodeType.Internal;
	}
	
	public PlaylistNodeSecondaryIndex(PlaylistNode parent, ArrayList<String> genres, ArrayList<PlaylistNode> children) {
		super(parent);
		this.genres = genres;
		this.children = children;
		this.type = PlaylistNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<PlaylistNode> getAllChildren()
	{
		return this.children;
	}
	
	public PlaylistNode getChildrenAt(Integer index) {
		
		return this.children.get(index);
	}
	

	public Integer genreCount()
	{
		return this.genres.size();
	}
	
	public String genreAtIndex(Integer index) {
		if(index >= this.genreCount() || index < 0) {
			return "Not Valid Index!!!";
		}
		else {
			return this.genres.get(index);
		}
	}



	// Extra functions if needed
	public void addGenre(int index, String genre)
	{	int already_there = genres.indexOf(genre);
		if(already_there==-1)genres.add(index,genre);
	}

	public void addChildren(PlaylistNode newNode )
	{
		children.add(newNode);
	}

	public void addChildrenatIndex(int i,PlaylistNode newNode )
	{
		children.add(i,newNode);
	}
	public int removeChildren(PlaylistNode Node )
	{
		int n = children.indexOf(Node);
		children.remove(Node);
		return n;
	}


}
